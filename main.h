#ifndef MAIN_H
#define MAIN_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <rtai.h>
#include "definitions.h"

#define SW_OPEN 0
#define SW_CLOSE 1
#define OFF 0
#define ON 1

#define ACTION_LAMP			0
#define ACTION_SOLENOID		1
#define ACTION_OFF			0
#define ACTION_CONTINOUS	1
#define ACTION_ONE_SHOT		2
#define ACTION_PULSE		3

#define DELAY				-1
#define FALSE 0
#define TRUE 1


#define GH_SWITCH_MATRIX 		0
#define GH_DIRECT_SWITCH		1
#define GH_USER_SPACE_MESSAGE	2
#define GH_DEFAULT				3

#define PT_LAMP				0
#define PT_FLASH			1

#define GAME				0
#define ATTRACT				1
#define DIAGNOSTIC			2



typedef unsigned short BYTE;
typedef void (*SWITCH_FUNCTION)(int sw, BYTE state);
typedef void (*EVENT_FUNCTION)(int param);

struct action {
	BYTE mode;
	RTIME stop_time;
	RTIME pulse_on_time;
	RTIME pulse_off_time;
	BYTE pulse_high;
	int pulse_cnt;
	int pulse_max;
	BYTE strength;
	EVENT_FUNCTION event;
	int param;
};


struct timer_struct {
	RTIME stop_time;
	EVENT_FUNCTION event;
	int param;
};



struct pattern_struct {
	int *data;
	int counter;
	int size;
	BYTE type;
	int timer_id;
	BYTE one_shot;
};


void send_msg(unsigned int msg);

void pattern_handler(int id);
int start_pattern(BYTE type, int *data, int items, BYTE one_shot);
void stop_pattern(int id);
void stop_all_patterns();

int timer(RTIME duration, EVENT_FUNCTION event, int param);
void clear_timer(int id);
void clear_all_timers(void);

BYTE get_switch(BYTE sw);
BYTE get_direct_switch(int sw);
BYTE get_lamp(BYTE lamp);
BYTE get_solenoid(BYTE solenoid);

void set_action(BYTE type, BYTE num, BYTE mode, BYTE strength, RTIME on_time, 
				RTIME off_time, int pulse_max, EVENT_FUNCTION event, int param);
void enable_lamp(BYTE lamp, BYTE strength);
void fire_lamp(BYTE lamp, BYTE strength, RTIME duration);
void pulse_lamp(BYTE lamp, BYTE strength, RTIME on_time, RTIME off_time, int pulse_max);
void disable_lamp(BYTE lamp);
void disable_lamps(void);

void enable_solenoid(BYTE solenoid);
void fire_solenoid(BYTE solenoid, RTIME duration);
void fire_solenoid_ex(BYTE solenoid, RTIME duration, EVENT_FUNCTION event);
void pulse_solenoid(BYTE solenoid, RTIME on_time, RTIME off_time, int pulse_max);
void disable_solenoid(BYTE solenoid);


#endif // MAIN_H
