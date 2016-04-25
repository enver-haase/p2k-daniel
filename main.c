
#include <rtai_sched.h>
#include <rtai_registry.h>
#include <rtai_sem.h>
#include <rtai_fifos.h>

#include "main.h"
#include "parport.h"
#include "definitions.h"
#include "game.h"
#include "diagnostic.h"

MODULE_DESCRIPTION("Pinball 2000");
MODULE_AUTHOR("***");

#define TICK_SWITCHES	 		400000
#define TICK_LAMP_MATRIXES 		1000000 //1000000  //1000000
#define TICK_SOLENOIDS 			2500000 //2500000

#define STACK_SIZE 20000

#define FIFO_SWITCH		0
#define FIFO_LAMP		1
#define FIFO_SEND		2
#define FIFO_RECIEVE	3

#define MAX_TIMERS		16
#define MAX_PATTERNS	16

static volatile BYTE switch_matrix[0x08];
static volatile BYTE direct_switches[0x14];

static RT_TASK thread_switches;
static RT_TASK thread_lamp_matrixes;
static RT_TASK thread_solenoids;

static volatile struct action lamp_matrix_action[0xff];
static volatile struct action solenoid_action[0xff];

static volatile struct timer_struct timers[MAX_TIMERS];
static volatile struct pattern_struct patterns[MAX_PATTERNS];

static SEM set_action_sem;
static SEM unset_action_sem;
static SEM fifo_sem;
static SEM send_msg_sem;

static SWITCH_FUNCTION *switch_matrix_function;
static SWITCH_FUNCTION *direct_switch_function;


// * * * Functions for sending and recieving data to and from userspace via FIFO:s.

void send_msg(unsigned int msg)
{
//	rt_sem_wait(&send_msg_sem);
	rtf_put(FIFO_SEND, &msg, sizeof(unsigned int));
//	rt_sem_signal(&send_msg_sem);
}

int recieve_msg(unsigned int fifo)
{
	unsigned int msg;
	rtf_get(fifo, &msg, sizeof(unsigned int));
	game_handler(GH_USER_SPACE_MESSAGE, (int)msg, 0);
	return 1;
}


// * * * Functions for handling lamps & flash lamps patterns

void pattern_handler(int id)
{
	int i;
	struct pattern_struct *pattern = (struct pattern_struct*) &patterns[id];
	int size = pattern->data[pattern->counter++];
	int duration = pattern->data[pattern->counter++];

	if (pattern->data[pattern->counter] == DELAY) 
	{
		pattern->counter++;
		pattern->timer_id = timer(duration, &pattern_handler, id);
	}
	else 
	{
		int duration_delay = pattern->data[pattern->counter++];
		for (i = 0; i < size; i++) 
		{
			if (pattern->type == PT_LAMP)
				fire_lamp(pattern->data[pattern->counter++], 1, duration + 5);
			else
				fire_solenoid(pattern->data[pattern->counter++], duration + 5);
		}
		pattern->timer_id = timer(duration_delay, &pattern_handler, id);
	}

	pattern->counter %= pattern->size;

	// Stop the pattern if it's a one_shot pattern and it's runned once.
	if (pattern->counter == 0 && pattern->one_shot == TRUE)
		stop_pattern(id);
}


int start_pattern(BYTE type, int *data, int size, BYTE one_shot)
{
	int i;
	for (i = 0; i < MAX_PATTERNS; i++)
	{
		if (patterns[i].data == 0)
		{
			patterns[i].type = type;
			patterns[i].data = data;
			patterns[i].counter = 0;
			patterns[i].size = (int) (size / sizeof(int));
			patterns[i].timer_id = -1;
			patterns[i].one_shot = one_shot;
			pattern_handler(i);
			return i;
		}
	}
	return -1;
}

void stop_pattern(int id)
{
	patterns[id].data = 0;
	if (patterns[id].timer_id != -1)
	{
		clear_timer(patterns[id].timer_id);
		patterns[id].timer_id = -1;
		patterns[id].data = 0;
	}
}

void stop_all_patterns()
{
	int i;
	for (i = 0; i < MAX_PATTERNS; i++)
	{
		stop_pattern(i);
	}	
}


// * * * Timer functions

int timer(RTIME duration, EVENT_FUNCTION event, int param)
{
	int i;
	for (i = 0; i < MAX_TIMERS; i++) 
	{
		if (timers[i].stop_time == 0) 
		{
			timers[i].stop_time = rt_get_time() + nano2count(duration * 1000000);
			timers[i].event = event;
			timers[i].param = param;
			return i;
		}
	}
	return -1;
}

void clear_timer(int id)
{
	timers[id].event = 0;
	timers[id].stop_time = 0;
}

void clear_all_timers()
{
	int i;
	for (i = 0; i < MAX_TIMERS; i++) 
		clear_timer(i);
}


// * * * Functions for getting the state of switches, directswitches, lamps and solenoids

BYTE get_switch(BYTE sw)
{
	return (switch_matrix[sw >> 4] & (1 << (sw & 0xf))) > 0;
}

BYTE get_direct_switch(int sw)
{
	return (direct_switches[sw >> 4] & (1 << (sw & 0xf))) > 0;
}

BYTE get_lamp(BYTE lamp)
{
	return lamp_matrix_action[lamp].mode > OFF;
}

BYTE get_solenoid(BYTE solenoid)
{
	return solenoid_action[solenoid].mode > OFF;
}


// * * * The main function for starting an action. Usually called from the short cut functions below...

void set_action(BYTE type, BYTE num, BYTE mode, BYTE strength, RTIME on_time, 
				RTIME off_time, int pulse_max, EVENT_FUNCTION event, int param)
{
	struct action *action_ptr;
	RTIME time;

	rt_sem_wait(&set_action_sem);

	if (type == ACTION_LAMP) {
		action_ptr = (struct action*) &lamp_matrix_action[num];
	}
	else {
		action_ptr = (struct action*) &solenoid_action[num];
	}

	action_ptr->strength = strength;
	action_ptr->event = event;
	action_ptr->param = param;


	if (action_ptr->strength == 0) { 
		action_ptr->strength = 1; 
	}

	time = nano2count(on_time * 1000000);
	action_ptr->stop_time = rt_get_time() + time;
	if (mode == ACTION_PULSE) {
		action_ptr->pulse_on_time = time;
		action_ptr->pulse_off_time = nano2count(off_time * 1000000);
		action_ptr->pulse_high = 1;
		action_ptr->pulse_max = pulse_max;
		action_ptr->pulse_cnt = 0;
	}
	else {
		action_ptr->pulse_high = 0;
	}
	action_ptr->mode = mode;
	rt_sem_signal(&set_action_sem);
}


// * * * Lamp handling functions

void enable_lamp(BYTE lamp, BYTE strength)
{
	set_action(ACTION_LAMP, lamp, ACTION_CONTINOUS, strength, 0, 0, 0, 0,0);
}

void fire_lamp(BYTE lamp, BYTE strength, RTIME duration)
{
	set_action(ACTION_LAMP, lamp, ACTION_ONE_SHOT, strength, duration, 0, 0, 0, 0);
}

void pulse_lamp(BYTE lamp, BYTE strength, RTIME on_time, RTIME off_time, int pulse_max)
{
	set_action(ACTION_LAMP, lamp, ACTION_PULSE, strength, on_time, off_time, pulse_max, 0, 0);
}

void disable_lamp(BYTE lamp)
{
	rt_sem_wait(&unset_action_sem);
	lamp_matrix_action[lamp].mode = ACTION_OFF;
	rt_sem_signal(&unset_action_sem);
}

void disable_lamps()
{
	int i;
	for (i = 0; i < 0xff; i++) 
	{
		lamp_matrix_action[i].mode = ACTION_OFF;
	}
}


// * * * Solenoid (and flash lamps) handling functions

void enable_solenoid(BYTE solenoid)
{
	set_action(ACTION_SOLENOID, solenoid, ACTION_CONTINOUS, 1, 0, 0, 0, 0,0);
}

void fire_solenoid(BYTE solenoid, RTIME duration)
{
	set_action(ACTION_SOLENOID, solenoid, ACTION_ONE_SHOT, 1, duration, 0, 0, 0 ,0);
}

void fire_solenoid_ex(BYTE solenoid, RTIME duration, EVENT_FUNCTION event)
{
	set_action(ACTION_SOLENOID, solenoid, ACTION_ONE_SHOT, 1, duration, 0, 0, event, 0);
}

void pulse_solenoid(BYTE solenoid, RTIME on_time, RTIME off_time, int pulse_max)
{
	set_action(ACTION_SOLENOID, solenoid, ACTION_PULSE, 1, on_time, off_time, pulse_max, 0, 0);
}

void disable_solenoid(BYTE solenoid)
{
	rt_sem_wait(&unset_action_sem);
	solenoid_action[solenoid].mode = ACTION_OFF;
	rt_sem_signal(&unset_action_sem);
}


// * * * Real time thread for handling the switch matrix and the direct switches

void switches_handler(long t)
{
	int direct_switch_banks[] = {REGISTER_SWITCH_FLIPPER, REGISTER_SWITCH_MISC, REGISTER_SWITCH_COIN, REGISTER_SWITCH_ZERO, 
								REGISTER_SWITCH_DIP, REGISTER_LAMP_A_DIAGNOSTIC, REGISTER_LAMP_B_DIAGNOSTIC,
	                            REGISTER_FUSE_A_DIAGNOSTIC, REGISTER_FUST_B_DIAGNOSTIC};
	BYTE data, col, row, bit, sw, col_val, bank, switches, bank_cnt;
	unsigned int fifodata;
	rt_printk("enter switches_handler\n");
	for (col = 0; col < 8; col++) {	switch_matrix[col] = 0;	}

	col = bank_cnt = 0;
	while(1) 
	{
		// * * * Switch matrix * * *
		col_val = (1 << col);// ^ 0xff;
		send_data(REGISTER_SWITCH_COLUMN,col_val);
		data = receive_data(REGISTER_SWITCH_ROW);
//		rt_printk("colum=%d, data=%x\n",col,data);

		fifodata = (col << 8) + data;
		rtf_put(0, &fifodata, sizeof(unsigned int));

        // Check if any row in current column has changed since last time
		if (data != switch_matrix[col]) {
            // Scan all bits to find the row(s) that has changed
			for (row = 0; row < 8; row++) {
				bit = 1 << row;
				if ((bit & data) != (bit & switch_matrix[col])) {
					sw = (col << 4) + row;

					if ((bit & data) == 0) switch_matrix[col] -= bit;
					else switch_matrix[col] += bit;

//					printk("sw=%x, state=%d\n",sw,(bit & data) != 0);
					game_handler(GH_SWITCH_MATRIX, sw, (bit & data) != 0);
				}
			}
		}


		// * * * Direct switches * * *
		if (col % 4 == 0) // Not necessary to check direct switches for every column checked in switch matrix or?
		{
			bank = direct_switch_banks[bank_cnt];
			data = receive_data(bank);

			fifodata = ((bank+8) << 8) + data;
			rtf_put(0, &fifodata, sizeof(unsigned int));

    	    // Check if any switch has changed since last time.
	        if (data != direct_switches[bank]) {
		        // Scan all bits to find the row that has changed
	            for (switches = 0; switches < 8; switches++) {
					bit = 1 << switches;
	                if ((bit & data) != (bit & direct_switches[bank])) {
						sw = (bank << 4) + switches;

						if ((bit & data) == 0) direct_switches[bank] -= bit;
						else direct_switches[bank] += bit;

						game_handler(GH_DIRECT_SWITCH, sw, (bit & data) != 0);
	                }
	            }
	        }

			bank_cnt = ++bank_cnt % 2; // Just test REGISTER_SWITCH_FLIPPER, REGISTER_SWITCH_MISC for now...
			
			// Call game handler with default parameter
			game_handler(GH_DEFAULT, 0, 0);
		}

		col = ++col % 8;
		rt_task_wait_period();
	}
}


// * * * Real time thread for handling the lamp matrixes (A & B)

void lamp_matrixes_handler(long t)
{
	BYTE col, row, lamp, strength_cnt, timer_cnt;
	BYTE lamp_data[2];
	struct action *action_ptr;
	RTIME time;
	unsigned int fifodata, i;
	static volatile BYTE prev_lamp_matrix_action[2][0x08];

	rt_printk("enter lamp_matrixes_handler\n");
	
	memset(&prev_lamp_matrix_action, 0, sizeof(prev_lamp_matrix_action));

	strength_cnt = 0;

	while(1) 
	{
		// Handle delays (nothing to do with lamps, but I got to place it somewere.
		// maybe I shall make a seperate thread for delays...)
		time = rt_get_time();
		for (timer_cnt = 0; timer_cnt < MAX_TIMERS; timer_cnt++)
		{
			if (timers[timer_cnt].stop_time != 0 && time > timers[timer_cnt].stop_time)
			{
				timers[timer_cnt].stop_time = 0;
				timers[timer_cnt].event(timers[timer_cnt].param);
			}
		}

		// * * * Lamp matrix A & B * * *
		for (col = 0; col < 8; col++) 
		{
			time = rt_get_time();
			lamp_data[0] = lamp_data[1] = 0;

			for (row = 0; row < 8; row++) 
			{
				for (lamp = (col << 4 | row); lamp < 0xff; lamp += 0x80) 
				{
					action_ptr = (struct action*) &lamp_matrix_action[lamp];

					if (action_ptr->mode == ACTION_OFF) continue;

					if ((action_ptr->mode != ACTION_PULSE || action_ptr->pulse_high) && 
						(strength_cnt % action_ptr->strength) == 0) 
					{
						lamp_data[lamp >> 7] |= (1 << row);
						if (action_ptr->mode == ACTION_CONTINOUS) continue;
					}

					if (time > action_ptr->stop_time) 
					{
						if (action_ptr->mode == ACTION_PULSE) 
						{
							if (action_ptr->pulse_high == 0) { action_ptr->pulse_cnt++; }
							action_ptr->pulse_high = !action_ptr->pulse_high;
							action_ptr->stop_time = time + 
								(action_ptr->pulse_high ? action_ptr->pulse_on_time : action_ptr->pulse_off_time);
						}

						if (action_ptr->mode != ACTION_PULSE || (action_ptr->mode == ACTION_PULSE &&
							action_ptr->pulse_cnt >= action_ptr->pulse_max && action_ptr->pulse_max > 0)) 
						{
							action_ptr->mode = ACTION_OFF;
							if (action_ptr->event > 0) 
							{
								action_ptr->event(lamp);
							}
						}
					}
				}
			}

			// Send lamp data to the power driver board
			send_data(REGISTER_LAMP_COLUMN,1 << col);
			send_data(REGISTER_LAMP_ROW_A,lamp_data[0]);
			send_data(REGISTER_LAMP_ROW_B,lamp_data[1]);


			/*
			// For testing lamp patterns...
			rt_sem_wait(&fifo_sem);
			for (i = 0; i < 2; i++) {
				if (prev_lamp_matrix_action[i][col] != lamp_data[i]) {
					fifodata = (i << 16) + (col << 8) + lamp_data[i];
					rtf_put(1, &fifodata, sizeof(unsigned int));
					prev_lamp_matrix_action[i][col] = lamp_data[i];
				}
			}
			rt_sem_signal(&fifo_sem);
			*/

			rt_task_wait_period();
		}
		
		strength_cnt = ++strength_cnt % 7;
	}
}


// * * * Real time thread for handling the solenoids (and flashes)

void solenoids_handler(long t)
{
	BYTE bank, sol, strength_cnt, sol_data;
	struct action *action_ptr;
	RTIME time;
	unsigned int fifodata;

	rt_printk("enter solenoids_handler\n");
	strength_cnt = 0;
	enable_solenoid(INTER_LOCK_RELAY);
	
	while(1) {
		for (bank = REGISTER_SOLENOID_C ; bank <= REGISTER_SOLENOID_LOGIC; bank++) {

			time = rt_get_time();
			sol_data = 0;

			for (sol = 0; sol < 8; sol++) {
				action_ptr = (struct action*) &solenoid_action[bank << 4 | sol];

				if (action_ptr->mode == ACTION_OFF) continue;

				if ((action_ptr->mode != ACTION_PULSE || action_ptr->pulse_high) && 
					(strength_cnt % action_ptr->strength) == 0) {
					sol_data |= (1 << sol);
					if (action_ptr->mode == ACTION_CONTINOUS) continue;
				}

				if (time > action_ptr->stop_time) {

					if (action_ptr->mode == ACTION_PULSE) {
						if (action_ptr->pulse_high == 0) { action_ptr->pulse_cnt++; }
						action_ptr->pulse_high = !action_ptr->pulse_high;
						action_ptr->stop_time = time + 
							(action_ptr->pulse_high ? action_ptr->pulse_on_time : action_ptr->pulse_off_time);
					}
					if (action_ptr->mode != ACTION_PULSE || (action_ptr->mode == ACTION_PULSE &&
						action_ptr->pulse_cnt >= action_ptr->pulse_max && action_ptr->pulse_max > 0)) {
						
						action_ptr->mode = ACTION_OFF;
						if (action_ptr->event > 0) {
							action_ptr->event(bank << 4 | sol);
						}
					}
				}


			}

//			fifodata = (bank << 16) + sol_data;
//			rtf_put(1, &fifodata, sizeof(unsigned int));

			send_data(bank,sol_data);
			rt_task_wait_period();
		}
	}
}


// * * * The modules init function (insmod pinball2000.ko).

int init_module(void)
{
	RTIME tick;
	unsigned int i;

	printk("Pinball 2000 driver - init module\n" );

	rt_sem_init(&set_action_sem, 1);	
	rt_sem_init(&unset_action_sem, 1);	
	rt_sem_init(&fifo_sem, 1);	

	// Fifo for sending switch and lamps data to user space program
	rtf_create(0,100);
	rtf_reset(0);
	rtf_create(1,100);
	rtf_reset(1);

	rtf_create(FIFO_SEND,100);
	rtf_reset(FIFO_SEND);
	rtf_create(FIFO_RECIEVE,100);
	rtf_reset(FIFO_RECIEVE);
	rtf_create_handler(FIFO_RECIEVE, &recieve_msg);
	rt_sem_init(&send_msg_sem, 1);	

	disable_lamps();
	clear_all_timers();
	stop_all_patterns();
	for (i = 0; i < 0xff; i++) solenoid_action[i].mode = ACTION_OFF;

	init_parport();
	init_game();
//	init_diagnostic();
	start_attract_mode(1);

//	switch_matrix_function = game_switch_matrix_function();
//	direct_switch_function = game_direct_switch_function();
//	switch_matrix_function = diagnostic_switch_matrix_function();
//	direct_switch_function = diagnostic_direct_switch_function();

	send_data(REGISTER_SOLENOID_D, 0x0);	//Solenoid set D FIRST CONTAINS INTERLOCK RELAY!!!
	send_data(REGISTER_SOLENOID_A, 0x0);	//Solenoid set A 
	send_data(REGISTER_SOLENOID_B, 0x0);	//Solenoid set B 
	send_data(REGISTER_SOLENOID_C,	0x0);	//Solenoid set C 
	send_data(REGISTER_SOLENOID_FLIPPER,0x0);	//Flipper solenoids
	send_data(REGISTER_SOLENOID_LOGIC,0x0);	//Logic-level drivers 

	rt_set_periodic_mode();

	// Init and start the switch matrix real time task
	rt_task_init(&thread_switches, switches_handler, 0, STACK_SIZE, 0, 0, 0);
	tick = start_rt_timer(nano2count(TICK_SWITCHES));
	rt_task_make_periodic(&thread_switches, rt_get_time() + tick, tick);

	// Init and start the lamp matrixes real time task
	rt_task_init(&thread_lamp_matrixes, lamp_matrixes_handler, 0, STACK_SIZE, 0, 0, 0);
	tick = start_rt_timer(nano2count(TICK_LAMP_MATRIXES));
	rt_task_make_periodic(&thread_lamp_matrixes, rt_get_time() + tick, tick);

	// Init and start the solenoid real time task
	rt_task_init(&thread_solenoids, solenoids_handler, 0, STACK_SIZE, 0, 0, 0);
	tick = start_rt_timer(nano2count(TICK_SOLENOIDS));
	rt_task_make_periodic(&thread_solenoids, rt_get_time() + tick, tick);

	return 0;
}


// * * * The modules exit function (rmmod pinball2000.ko).

void cleanup_module(void)
{
//	BYTE col, data;
	// disable real time tasks
	rt_task_delete(&thread_solenoids);
	rt_task_delete(&thread_lamp_matrixes);
	rt_task_delete(&thread_switches);

	// disable solenoids
/*	data = 0;
	send_data(REGISTER_SOLENOID_D, data);
	send_data(REGISTER_SOLENOID_C, 0);
	send_data(REGISTER_SOLENOID_B, 0);
	send_data(REGISTER_SOLENOID_A, 0);
	send_data(REGISTER_SOLENOID_FLIPPER, 0);
	send_data(REGISTER_SOLENOID_LOGIC, 0);

	// disable lamps
	for (col = 0; col < 8; col++) {
		send_data(REGISTER_LAMP_COLUMN,col);
		send_data(REGISTER_LAMP_ROW_A, 0);
		send_data(REGISTER_LAMP_ROW_B, 0);
	}
*/

	cleanup_parport();

	printk("Pinball 2000 driver - cleanup module\n" );
	return;
}
