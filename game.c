
s#include "game.h"
#include "definitions.h"
#include "attract.h"

static SWITCH_FUNCTION switch_matrix_function[0x7f];
static SWITCH_FUNCTION direct_switch_function[0x13f];

int mael_lamp_ids[] = {LAMP_MAEL_M, LAMP_MAEL_A, LAMP_MAEL_E, LAMP_MAEL_L};
int ron_lamp_ids[] = {LAMP_RON_R, LAMP_RON_O, LAMP_RON_N};
int russell_lamps_ids[] = {LAMP_RUSSELL_R, LAMP_RUSSELL_U, LAMP_RUSSELL_S1, LAMP_RUSSELL_S2, 
							LAMP_RUSSELL_E, LAMP_RUSSELL_L1, LAMP_RUSSELL_L2};

int mael_lamps[4];
int ron_lamps[3];
int sparks_lamps[6];
int russell_lamps;
int multiball_hits[5];

int multiball;
int ballsave;
int game_is_running;
int kickback_active;
int launch_mode; // 0=ingen, 1=manuell, 2=automatic

int bumper_hits;
int spinner_turns;
int ready_for_multiball;
int super_jackpot_lit;
int super_jackpot_cnt;
int super_duper_jackpot_lit;
int shooter_lane_pattern_id;

/*
SWITCH_FUNCTION* game_switch_matrix_function(void) {	return switch_matrix_function;}
SWITCH_FUNCTION* game_direct_switch_function(void) {	return direct_switch_function; }
*/



int backboard_pattern1[] = 
{
1, 5, 30, FLASHER_BACK_PANEL_1, 
1, 5, 30, FLASHER_BACK_PANEL_2, 
1, 5, 30, FLASHER_BACK_PANEL_3, 
1, 5, 30, FLASHER_BACK_PANEL_2, 
1, 5, 30, FLASHER_BACK_PANEL_1, 
1, 5, 30, FLASHER_BACK_PANEL_2, 
1, 5, 30, FLASHER_BACK_PANEL_3, 
};

int backboard_pattern2[] = 
{
1, 5, 30, FLASHER_BACK_PANEL_7, 
1, 5, 30, FLASHER_BACK_PANEL_6, 
1, 5, 30, FLASHER_BACK_PANEL_5, 
1, 5, 30, FLASHER_BACK_PANEL_6, 
1, 5, 30, FLASHER_BACK_PANEL_7, 
1, 5, 30, FLASHER_BACK_PANEL_6, 
1, 5, 30, FLASHER_BACK_PANEL_5, 
};

int backboard_pattern3[] = 
{
1, 5, 60, FLASHER_BACK_PANEL_4, 
2, 5, 60, FLASHER_BACK_PANEL_3, FLASHER_BACK_PANEL_5, 
2, 5, 60, FLASHER_BACK_PANEL_2, FLASHER_BACK_PANEL_6, 
2, 5, 60, FLASHER_BACK_PANEL_1, FLASHER_BACK_PANEL_7, 
2, 5, 60, FLASHER_BACK_PANEL_2, FLASHER_BACK_PANEL_6, 
2, 5, 60, FLASHER_BACK_PANEL_3, FLASHER_BACK_PANEL_5, 
1, 5, 60, FLASHER_BACK_PANEL_4, 
};

int backboard_pattern4[] = 
{
2, 15, 60, FLASHER_BACK_PANEL_1, FLASHER_BACK_PANEL_7, 
2, 15, 60, FLASHER_BACK_PANEL_2, FLASHER_BACK_PANEL_6, 
2, 15, 60, FLASHER_BACK_PANEL_3, FLASHER_BACK_PANEL_5, 
1, 15, 60, FLASHER_BACK_PANEL_4, 
2, 15, 60, FLASHER_BACK_PANEL_3, FLASHER_BACK_PANEL_5, 
2, 15, 60, FLASHER_BACK_PANEL_2, FLASHER_BACK_PANEL_6, 
2, 15, 60, FLASHER_BACK_PANEL_1, FLASHER_BACK_PANEL_7, 
};

int shooter_lane_pattern[] = 
{
1, 80, 80, LAMP_SHOOTER_LANE_1, 
1, 80, 80, LAMP_SHOOTER_LANE_2, 
1, 80, 80, LAMP_SHOOTER_LANE_3, 
1, 80, 80, LAMP_SHOOTER_LANE_4, 
1, 80, 80, LAMP_SHOOTER_LANE_5, 
};



void eject_ball(int sw)
{
	fire_solenoid(SOLENOID_THROUGH_EJECT, 100);
}


void ballsave_handler(int param)
{
	if (ballsave == TRUE && param == 0)
	{
		timer(10000,ballsave_handler,1);
	}
	else
	{
		disable_lamp(LAMP_SHOOT_AGAIN);
		ballsave = FALSE;
	}
}


void sparks_lamps_handler(int sw, int play_pattern)
{
	if (multiball == TRUE)
		return;

	int ok_to_play_pattern = FALSE;	

	if ((sw == SWITCH_MAEL_M || sw == SWITCH_MAEL_A || sw == SWITCH_MAEL_E || 
			sw == SWITCH_MAEL_L) && sparks_lamps[0] == 0)
	{
		sparks_lamps[0] = 1;
		ok_to_play_pattern = TRUE;
		enable_lamp(LAMP_SPARKS_S1, 1);
		send_msg(KERNEL_EVENT_S);
	}
	else if ((sw == SWITCH_DROP_TARGET_LEFT || sw == SWITCH_DROP_TARGET_MIDDLE || 
				sw == SWITCH_DROP_TARGET_RIGHT) && sparks_lamps[1] == 0)
	{
		sparks_lamps[1] = 1;
		ok_to_play_pattern = TRUE;
		enable_lamp(LAMP_SPARKS_P, 1);
		send_msg(KERNEL_EVENT_P);
	}
	else if (sw == SWITCH_CAPTIVE_BALL && sparks_lamps[2] == 0)
	{
		sparks_lamps[2] = 1;
		disable_lamp(LAMP_CAPTIVE_BALL);
		ok_to_play_pattern = TRUE;
		enable_lamp(LAMP_SPARKS_A, 1);
		send_msg(KERNEL_EVENT_A);
	}
	else if (sw == SWITCH_ALLEY_TARGET_UPPER &&  sparks_lamps[3] == 0)
	{
		sparks_lamps[3] = 1;
		ok_to_play_pattern = TRUE;
		enable_lamp(LAMP_SPARKS_R, 1);
		send_msg(KERNEL_EVENT_R);
	}
	else if ((sw == SWITCH_RON_R || sw == SWITCH_RON_O || sw == SWITCH_RON_N)  && sparks_lamps[4] == 0)
	{
		sparks_lamps[4] = 1;
		ok_to_play_pattern = TRUE;
		disable_lamp(LAMP_LEFT_LOOP);
		enable_lamp(LAMP_SPARKS_K, 1);
		send_msg(KERNEL_EVENT_K);

	}
	else if (sw == SWITCH_SPINNER && spinner_turns == 15)
	{
		sparks_lamps[5] = 1;
		ok_to_play_pattern = TRUE;
		disable_lamp(LAMP_RIGHT_LOOP);
		enable_lamp(LAMP_SPARKS_S2, 1);
		send_msg(KERNEL_EVENT_S);
	}

	if (ok_to_play_pattern == TRUE && play_pattern == TRUE)
	{
		start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);
	}

	if (sparks_lamps[0] > 0 && sparks_lamps[1] > 0 && sparks_lamps[2] > 0 &&
		sparks_lamps[3] > 0 && sparks_lamps[4] > 0 && sparks_lamps[5] > 0)
	{
		ready_for_multiball = TRUE;
		pulse_lamp(LAMP_JACKPOT_RIGHT_LOOP, 1,150,150,0);
		pulse_lamp(LAMP_RIGHT_LOOP, 1,150,150,0);
	}
}


void mael_lanes(int sw, BYTE state)
{
	int i;
	int kickback_fired = FALSE;

	if (state == SW_OPEN) {	return;	}

	if (sw == SWITCH_MAEL_M && kickback_active) 
	{
		fire_solenoid(SOLENOID_KICKBACK, 80);
		start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);
		disable_lamp(LAMP_KICKBACK);
		send_msg(KERNEL_EVENT_KICKBACK_FIRED);
		kickback_active = FALSE;
		kickback_fired = TRUE;
	}

	if (sw == SWITCH_MAEL_M && mael_lamps[0] == FALSE) { enable_lamp(LAMP_MAEL_M, 1); mael_lamps[0] = TRUE; }
	if (sw == SWITCH_MAEL_A && mael_lamps[1] == FALSE) { enable_lamp(LAMP_MAEL_A, 1); mael_lamps[1] = TRUE; }
	if (sw == SWITCH_MAEL_E && mael_lamps[2] == FALSE) { enable_lamp(LAMP_MAEL_E, 1); mael_lamps[2] = TRUE; }
	if (sw == SWITCH_MAEL_L && mael_lamps[3] == FALSE) { enable_lamp(LAMP_MAEL_L, 1); mael_lamps[3] = TRUE; }

	if (mael_lamps[0] == TRUE && mael_lamps[1] == TRUE && mael_lamps[2] == TRUE && mael_lamps[3] == TRUE) 
	{
		for (i = 0; i < 4; i++) {
			mael_lamps[i] = FALSE;
			disable_lamp(mael_lamp_ids[i]);
		}

		kickback_active = TRUE;
		pulse_lamp(LAMP_KICKBACK, 1, 250,250,0);
		if (kickback_fired == FALSE)
		{
			sparks_lamps_handler(sw, TRUE);
			start_pattern(PT_FLASH, backboard_pattern3, sizeof(backboard_pattern3), TRUE);
			send_msg(KERNEL_EVENT_MAEL_SPELLED);
		}
		else
		{
			sparks_lamps_handler(sw, FALSE);
		}
	}
	else if (kickback_fired == FALSE)
	{
		send_msg(KERNEL_EVENT_MAEL_SWITCH);
	}

}


void ron_lanes(int sw, BYTE state)
{
	int i;

	if (state == SW_OPEN) {	return;	}

	send_msg(KERNEL_EVENT_RON_SWITCH);
	ballsave_handler(0);
	
	if (sw == SWITCH_RON_R && ron_lamps[0] == FALSE) { enable_lamp(LAMP_RON_R, 1); ron_lamps[0] = TRUE; }
	if (sw == SWITCH_RON_O && ron_lamps[1] == FALSE) { enable_lamp(LAMP_RON_O, 1); ron_lamps[1] = TRUE; }
	if (sw == SWITCH_RON_N && ron_lamps[2] == FALSE) { enable_lamp(LAMP_RON_N, 1); ron_lamps[2] = TRUE; }

	if (ron_lamps[0] == TRUE && ron_lamps[1] == TRUE && ron_lamps[2]) {
		send_msg(KERNEL_EVENT_RON_SPELLED);
		start_pattern(PT_FLASH, backboard_pattern3, sizeof(backboard_pattern3), TRUE);
		sparks_lamps_handler(sw, TRUE);
		for (i = 0; i < 3; i++) {
			ron_lamps[i] = FALSE;
			disable_lamp(ron_lamp_ids[i]);
		}
	}

}


void coin_door(int sw, BYTE state)
{
//	rt_printk("COIN DOOR sw=%x, state=%d, time=%d\n", sw, state, time);
//	set_action(ACTION_SOLENOID, INTER_LOCK_RELAY, state * ACTION_CONTINOUS, 0, 1);
}


void rotating_lamps_handler(int direction)
{
	int old_lamps[4];
	int i, j;
	int size = 4;
	int* lamps = mael_lamps;
	int* lamp_ids = mael_lamp_ids;

	// First mael lamps then ron lamps...
	for (j = 0; j < 2; j++)
	{
		for (i = 0; i < size; i++)	old_lamps[i] = lamps[i];

		if (direction == 1) { // Rotate right
			for (i = size-1; i > 0; i--) lamps[i] = old_lamps[i-1];
			lamps[0] = old_lamps[size-1];
		}
		else { // Rotate left
			for (i = 0; i < size-1; i++) lamps[i] = old_lamps[i+1];
			lamps[size-1] = old_lamps[0];
		}

		// Change the state of the lamps if necessary...
		for (i = 0; i < size; i++) {
			if (lamps[i] == TRUE)
				enable_lamp(lamp_ids[i], 1);
			else
				disable_lamp(lamp_ids[i]);
		}

		size = 3;
		lamps = ron_lamps;
		lamp_ids = ron_lamp_ids;
	}
}


void reset_multiball()
{
	int i;
	for (i = 0; i < 5; i++) multiball_hits[i] = 0;

	super_jackpot_lit = FALSE;
	super_jackpot_cnt=0;
	super_duper_jackpot_lit = FALSE;
	//disable_lamps();
	disable_lamp(LAMP_JACKPOT_CENTER_LEFT);
	disable_lamp(LAMP_JACKPOT_CENTER_RIGHT);
	disable_lamp(LAMP_JACKPOT_RIGHT_HOLE);
	pulse_lamp(LAMP_JACKPOT_LEFT_LOOP,1,150,150,0);
	pulse_lamp(LAMP_JACKPOT_UPPER_CENTER,1,150,150,0);
	pulse_lamp(LAMP_JACKPOT_RIGHT_LOOP,1,150,150,0);
}


void jackpot_event(int param)
{
	reset_multiball();
}


void multiball_handler(int sw)
{
	if (multiball == FALSE ) return;

	if (sw == SWITCH_LEFT_LOOP_UPPER && multiball_hits[0] == 0)
	{
		multiball_hits[0] = 1;
		send_msg(KERNEL_EVENT_JACKPOT);
		disable_lamp(LAMP_JACKPOT_LEFT_LOOP);
	}
	else if (sw == SWITCH_UPPER_LEFT_TARGET && multiball_hits[1] == 0)
	{
		multiball_hits[1] = 1;
		send_msg(KERNEL_EVENT_JACKPOT_UPPER_LEFT);
		disable_lamp(LAMP_JACKPOT_UPPER_CENTER);
	}
	else if (sw == SWITCH_SPINNER && multiball_hits[2] == 0)
	{
		multiball_hits[2] = 1;
		send_msg(KERNEL_EVENT_JACKPOT);
		disable_lamp(LAMP_JACKPOT_RIGHT_LOOP);
	}


	if (sw == SWITCH_RIGHT_SAUCER && super_duper_jackpot_lit == TRUE)
	{
		start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);
		reset_multiball();
		send_msg(KERNEL_EVENT_SUPER_DUPER_JACKPOT);
	}
	else if (sw == SWITCH_CENTER_TARGET && super_jackpot_lit == TRUE)
	{
		start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);
		super_jackpot_cnt++;
		if (super_jackpot_cnt == 1)
			send_msg(KERNEL_EVENT_SUPER_JACKPOT_1);
		else if (super_jackpot_cnt == 2)
			send_msg(KERNEL_EVENT_SUPER_JACKPOT_2);
		else if (super_jackpot_cnt == 3)
		{
			pulse_lamp(LAMP_JACKPOT_RIGHT_HOLE,1,150,150,0);
			super_duper_jackpot_lit = TRUE;
			send_msg(KERNEL_EVENT_SUPER_JACKPOT);
			timer(30000,jackpot_event,1);
			disable_lamp(LAMP_JACKPOT_CENTER_LEFT);
			disable_lamp(LAMP_JACKPOT_CENTER_RIGHT);
		}
	}
	else if (multiball_hits[0] == 1 && multiball_hits[1] == 1 && multiball_hits[2] == 1)
	{
		super_jackpot_lit = TRUE;
		pulse_lamp(LAMP_JACKPOT_CENTER_LEFT,1,150,150,0);
		pulse_lamp(LAMP_JACKPOT_CENTER_RIGHT,1,150,150,0);
		timer(30000,jackpot_event,0);

	}

}


void temp_flipper_power_end(int sol)
{
	if (sol == SOLENOID_LOWER_RIGHT_FLIPPER_POWER && get_direct_switch(SWITCH_RIGHT_FLIPPER_BUTTON) == SW_CLOSE)
	{
		enable_solenoid(SOLENOID_LOWER_RIGHT_FLIPPER_HOLD);
	}
	else if (sol == SOLENOID_LOWER_LEFT_FLIPPER_POWER && get_direct_switch(SWITCH_LEFT_FLIPPER_BUTTON) == SW_CLOSE)
	{
		enable_solenoid(SOLENOID_LOWER_LEFT_FLIPPER_HOLD);
	}
}


void flipper(int sw, BYTE state)
{
	static int right_active = 0;
	static int left_active = 0;

	if (state == SW_OPEN) 
	{
		if (sw == SWITCH_RIGHT_FLIPPER_BUTTON) 
		{
			right_active = 0;
			disable_solenoid(SOLENOID_LOWER_RIGHT_FLIPPER_POWER);
			disable_solenoid(SOLENOID_LOWER_RIGHT_FLIPPER_HOLD);
		}
		else if (sw == SWITCH_LEFT_FLIPPER_BUTTON) 
		{
			left_active = 0;
			disable_solenoid(SOLENOID_LOWER_LEFT_FLIPPER_POWER);
			disable_solenoid(SOLENOID_LOWER_LEFT_FLIPPER_HOLD);
		}
	}
	else 
	{
		if (sw == SWITCH_RIGHT_FLIPPER_BUTTON) 
		{
			right_active = 1;
			fire_solenoid_ex(SOLENOID_LOWER_RIGHT_FLIPPER_POWER, 100, temp_flipper_power_end);
			rotating_lamps_handler(1);
		}
		else if (sw == SWITCH_LOWER_RIGHT_FLIPPER_EOS && right_active == 1) 
		{
			enable_solenoid(SOLENOID_LOWER_RIGHT_FLIPPER_HOLD);
			disable_solenoid(SOLENOID_LOWER_RIGHT_FLIPPER_POWER);
		}
		else if (sw == SWITCH_LEFT_FLIPPER_BUTTON) 
		{
			left_active = 1;
			fire_solenoid_ex(SOLENOID_LOWER_LEFT_FLIPPER_POWER, 100, temp_flipper_power_end);
			rotating_lamps_handler(-1);
		}
		else if (sw == SWITCH_LOWER_LEFT_FLIPPER_EOS && left_active == 1) 
		{
			enable_solenoid(SOLENOID_LOWER_LEFT_FLIPPER_HOLD);
			disable_solenoid(SOLENOID_LOWER_LEFT_FLIPPER_POWER);
		}
	}
}


void action_button(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }

	if (get_direct_switch(SWITCH_LEFT_ACTION_BUTTON) == SW_CLOSE && 
		get_direct_switch(SWITCH_RIGHT_ACTION_BUTTON) == SW_CLOSE)
	{
		if (russell_lamps > 0)
		{
			start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);
			fire_solenoid(SOLENOID_MAGNET, 200);
			russell_lamps--;
			disable_lamp(russell_lamps_ids[russell_lamps]);
		}
	}

}


void tilt(int sw, BYTE state)
{
	if (state == SW_OPEN) {	return;	}
	send_msg(KERNEL_EVENT_TILT);
}


void spinner(int sw, BYTE state)
{
	if (state == SW_CLOSE)
	{
		spinner_turns++;
		fire_solenoid(FLASHER_BACK_PANEL_6, 15);
		sparks_lamps_handler(sw, TRUE);
		multiball_handler(sw);
	}
	send_msg(state == SW_CLOSE ? KERNEL_EVENT_SPINNER_ON : KERNEL_EVENT_SPINNER_OFF);
}


void sling_shot(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	send_msg(KERNEL_EVENT_SLING_SHOT);

	if (sw == SWITCH_LEFT_SLINGSHOT) 
	{
		fire_solenoid(SOLENOID_LEFT_SLINGSHOT, 25);
		fire_solenoid(FLASHER_BACK_PANEL_1, 15);
	}
	else 
	{
		fire_solenoid(SOLENOID_RIGHT_SLINGSHOT, 25);
		fire_solenoid(FLASHER_BACK_PANEL_7, 15);
	}
}


void captive_ball(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	sparks_lamps_handler(sw, TRUE);
	send_msg(KERNEL_EVENT_CAPTIVE_BALL);
}


void saucer_event(int sw)
{
	if (sw == SWITCH_RIGHT_SAUCER)
	{
		multiball_handler(sw);
		fire_solenoid(SOLENOID_RIGHT_SAUCER,100);
	}
	else
	{
		if (ready_for_multiball == TRUE)
		{	
			ready_for_multiball = FALSE;
			multiball = TRUE;
			send_msg(KERNEL_EVENT_MULTIBALL);
			fire_solenoid(SOLENOID_THROUGH_EJECT, 100);
			reset_multiball();

			disable_lamp(LAMP_RIGHT_LOOP);
		}
		fire_solenoid(SOLENOID_UPPER_SAUCER,100);
	}
}


void saucer_sw(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	if (sw == SWITCH_RIGHT_SAUCER) {
		if (multiball == FALSE)
		{
			send_msg(KERNEL_EVENT_RIGHT_HOLE);
		}
		timer(500,saucer_event,sw);
	}
	else
	{
		send_msg(KERNEL_EVENT_UPPER_HOLE);
		timer(500,saucer_event,sw);
	}
}


void center_target(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	multiball_handler(sw);
}


void left_loop(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	static RTIME sw_lower_time = 0;

	if (sw == SWITCH_LEFT_LOOP_LOWER)
	{
		sw_lower_time = rt_get_time();
	}
	else
	{
		RTIME diff_time = rt_get_time() - sw_lower_time;
		start_pattern(PT_FLASH, backboard_pattern1, sizeof(backboard_pattern1), TRUE);
		printk("send_msg diff_time=%d\n",diff_time);
		multiball_handler(sw);
		if (diff_time < 100000)
		{
			//send_msg(KERNEL_EVENT_LEFT_LOOP);
		}
	}
}


void upper_left_target(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	//fire_solenoid(FLASHER_BACK_PANEL_2, 15);
	if (multiball == TRUE)
	{
		multiball_handler(sw);
	}
	else
	{
		send_msg(KERNEL_EVENT_UPPER_LEFT_TARGET);
	}
}


void alley_target_sw(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }

	if (sw == SWITCH_ALLEY_TARGET_UPPER) {
		disable_lamp(LAMP_ALLEY_TARGET);
		disable_lamp(LAMP_ALLEY_ENTRANCE);
		sparks_lamps_handler(sw, TRUE);
	}
	start_pattern(PT_FLASH, backboard_pattern1, sizeof(backboard_pattern1), TRUE);
}


void pop_bumper(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }

	bumper_hits++;
	send_msg(KERNEL_EVENT_BUMPER_HIT);

	if (sw == SWITCH_BUMPER_UPPER) 
	{
		fire_solenoid(SOLENOID_BUMPER_UPPER, 25);
		fire_solenoid(FLASHER_BACK_PANEL_3, 15);
		fire_lamp(LAMP_BUMPER_LEFT, 1, 100);
	}
	else if (sw == SWITCH_BUMPER_RIGHT) 
	{
		fire_solenoid(SOLENOID_BUMPER_RIGHT, 25);
		fire_solenoid(FLASHER_BACK_PANEL_5, 15);
		fire_lamp(LAMP_BUMPER_RIGHT, 1, 100);
	}
	else if (sw == SWITCH_BUMPER_LOWER) 
	{
		fire_solenoid(SOLENOID_BUMPER_LOWER, 25);
		fire_solenoid(FLASHER_BACK_PANEL_4, 15);
		fire_lamp(LAMP_BUMPER_LOWER, 1, 100);
	}		
}


void drop_target(int sw, BYTE state)
{
	if (state == SW_CLOSE) { return; }

	if (get_switch(SWITCH_DROP_TARGET_LEFT) == SW_OPEN && 
		get_switch(SWITCH_DROP_TARGET_MIDDLE) == SW_OPEN && 
		get_switch(SWITCH_DROP_TARGET_RIGHT) == SW_OPEN)
	{
		pulse_lamp(LAMP_DROP_TARGET_LEFT, 1, 150,150,0);
		pulse_lamp(LAMP_DROP_TARGET_RIGHT, 1, 150,150,0);
		pulse_lamp(LAMP_DROP_TARGET_MIDDLE, 1, 150,150,0);
		start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);
		fire_solenoid(SOLENOID_DROP_TARGET_BANK, 100);
		sparks_lamps_handler(sw, TRUE);
		if (russell_lamps < 7)
		{
			enable_lamp(russell_lamps_ids[russell_lamps], 1);
			russell_lamps++;
		}
		send_msg(KERNEL_EVENT_ALL_DROPTARGET_BANK);
	}
	else
	{
		if (sw == SWITCH_DROP_TARGET_LEFT)
		{
			disable_lamp(LAMP_DROP_TARGET_LEFT);
		}
		else if (sw == SWITCH_DROP_TARGET_MIDDLE)
		{
			disable_lamp(LAMP_DROP_TARGET_MIDDLE);
		}
		else if (sw == SWITCH_DROP_TARGET_RIGHT)
		{
			disable_lamp(LAMP_DROP_TARGET_RIGHT);
		}
	}
}


void auto_launch_event(int sw)
{
	fire_solenoid(SOLENOID_AUTO_LAUNCH, 50);
}


void shooter_lane(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	if (sw == SWITCH_SHOOTER_LANE_LOWER)
	{
		timer(400,auto_launch_event, sw);
	}
	else
	{
		if (shooter_lane_pattern_id != -1)
		{
			stop_pattern(shooter_lane_pattern_id);
			shooter_lane_pattern_id = -1;
		}
		ballsave_handler(0);
		start_pattern(PT_FLASH, backboard_pattern2, sizeof(backboard_pattern2), TRUE);
//		if (get_switch(SWITCH_THROUGH_BALL_1) == SW_OPEN) 
//		{
//			fire_solenoid(SOLENOID_THROUGH_EJECT, 100);
//		}
	}
}


void diagnostics_button(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	printk("diagnostics_button=%x\n",sw);
	start_pattern(PT_FLASH, backboard_pattern4, sizeof(backboard_pattern4), TRUE);

	//fire_solenoid(FLASHER_BACK_PANEL_7, 25);

}


void game_handler(int type, int data, BYTE state)
{
	if (type == GH_SWITCH_MATRIX && switch_matrix_function[data] != 0)
	{
//		printk("switch_matrix=%x:%d, time=%d\n",data,state,rt_get_time());
		switch_matrix_function[data](data, state);
	}
	else if (type == GH_DIRECT_SWITCH && direct_switch_function[data] != 0)
	{
//		printk("direct_switch=%x:%d\n",data,state);
		direct_switch_function[data](data, state);
	}
	else if (type == GH_USER_SPACE_MESSAGE)
	{
		switch (data)
		{
			case USERSPACE_EVENT_RELEASE_UPPER_HOLE :
				printk("USERSPACE_EVENT_RELEASE_UPPER_HOLE\n" );
				break;
			case USERSPACE_EVENT_RELEASE_RIGHT_HOLE :
				printk("USERSPACE_EVENT_RELEASE_RIGHT_HOLE\n" );
				fire_solenoid(SOLENOID_RIGHT_SAUCER,100);
				break;
		}
	}
	else
	{
		// Check number of balls
		int balls_in_through;
		balls_in_through = 0;
		if (get_switch(SWITCH_THROUGH_JAM) == SW_OPEN) 		{ balls_in_through++; }
		if (get_switch(SWITCH_THROUGH_BALL_1) == SW_OPEN) 	{ balls_in_through++; }
		if (get_switch(SWITCH_THROUGH_BALL_2) == SW_OPEN) 	{ balls_in_through++; }
		if (get_switch(SWITCH_THROUGH_BALL_3) == SW_OPEN) 	{ balls_in_through++; }
		if (get_switch(SWITCH_THROUGH_BALL_4) == SW_OPEN) 	{ balls_in_through++; }
//		rt_printk("balls_in_through=%d\n", balls_in_through);
		if (balls_in_through == 4 && game_is_running == TRUE && ballsave == TRUE)
		{
			//fire_solenoid(SOLENOID_THROUGH_EJECT, 100);
		}
		
	}
}


void init_normal_mode()
{
	int i;

	spinner_turns = 0;
	multiball = FALSE;
	ready_for_multiball = FALSE;

	// Russell-magnet-lamps. 
	russell_lamps = 3;
	for (i = 0; i < russell_lamps; i++)
		enable_lamp(russell_lamps_ids[i], 1);

	pulse_lamp(LAMP_LEFT_LOOP, 1, 150,150,0);

	// Sparks-lamps
	for (i = 0; i < 6; i++) { sparks_lamps[i] = 0; }
	pulse_lamp(LAMP_SPARKS_S1, 1, 150,150,0);
	pulse_lamp(LAMP_SPARKS_P, 1, 150,150,0);
	pulse_lamp(LAMP_SPARKS_A, 1, 150,150,0);
	pulse_lamp(LAMP_SPARKS_R, 1, 150,150,0);
	pulse_lamp(LAMP_SPARKS_K, 1, 150,150,0);
	pulse_lamp(LAMP_SPARKS_S2, 1, 150,150,0);

	
	pulse_lamp(LAMP_CAPTIVE_BALL, 1, 150,150,0);
	pulse_lamp(LAMP_DROP_TARGET_LEFT, 1, 150,150,0);
	pulse_lamp(LAMP_DROP_TARGET_RIGHT, 1, 150,150,0);
	pulse_lamp(LAMP_DROP_TARGET_MIDDLE, 1, 150,150,0);
	pulse_lamp(LAMP_ALLEY_ENTRANCE, 1, 150,150,0);
	pulse_lamp(LAMP_RIGHT_LOOP, 1, 150,150,0);
	pulse_lamp(LAMP_LEFT_LOOP, 1, 150,150,0);
}


void new_game(void)
{
	int i;
	stop_attract_mode();
	bumper_hits = 0;
	game_is_running = TRUE;
	kickback_active = TRUE;
	send_msg(KERNEL_EVENT_GAME_STARTED);
	enable_lamp(LAMP_UPPER_LEFT_SPOTLIGHT,1);
	enable_lamp(LAMP_LOWER_LEFT_SPOTLIGHT,1);
	enable_lamp(LAMP_RIGHT_SPOTLIGHT,1);
	pulse_lamp(LAMP_KICKBACK, 1, 250,250,0);
	fire_solenoid(SOLENOID_DROP_TARGET_BANK, 100);

	for (i = 0; i < 4; i++) mael_lamps[i] = FALSE;
	for (i = 0; i < 3; i++) ron_lamps[i] = FALSE;

	init_normal_mode();
}


void start_button(int sw, BYTE state)
{
	if (state == SW_OPEN) { return; }
	if (game_is_running == FALSE) new_game();
	if (shooter_lane_pattern_id == -1)
		shooter_lane_pattern_id = start_pattern(PT_LAMP, shooter_lane_pattern, sizeof(shooter_lane_pattern), FALSE);
	ballsave = TRUE;	
	pulse_lamp(LAMP_SHOOT_AGAIN, 1, 300,300,0);
	fire_solenoid(SOLENOID_THROUGH_EJECT, 100);
}


void init_game(void)
{
	multiball = FALSE;
	ballsave = FALSE;
	launch_mode=0;
	shooter_lane_pattern_id = -1;
	game_is_running = FALSE;
	memset(switch_matrix_function, 0, 0x7f);
	memset(direct_switch_function, 0, 0x13f);
	/*
	int unsigned i;
	for (i = 0; i < 0x7f; i++) switch_matrix_function[i] = 0; //&default_switch_matrix_function;
	for (i = 0; i < 0x13f; i++) direct_switch_function[i] = 0; //&default_direct_switch_function;
	*/
	
	switch_matrix_function[SWITCH_START_BUTTON] = &start_button;
	switch_matrix_function[SWITCH_SPINNER] = &spinner;
	switch_matrix_function[SWITCH_CENTER_TARGET] = &center_target;
	switch_matrix_function[SWITCH_UPPER_LEFT_TARGET] = &upper_left_target;
	switch_matrix_function[SWITCH_LEFT_LOOP_LOWER] = &left_loop;
	switch_matrix_function[SWITCH_LEFT_LOOP_UPPER] = &left_loop;

	switch_matrix_function[SWITCH_DROP_TARGET_LEFT] = &drop_target;
	switch_matrix_function[SWITCH_DROP_TARGET_MIDDLE] = &drop_target;
	switch_matrix_function[SWITCH_DROP_TARGET_RIGHT] = &drop_target;

	switch_matrix_function[SWITCH_SHOOTER_LANE_LOWER] = &shooter_lane;
	switch_matrix_function[SWITCH_SHOOTER_LANE_UPPER] = &shooter_lane;

	switch_matrix_function[SWITCH_BUMPER_UPPER] = &pop_bumper;
	switch_matrix_function[SWITCH_BUMPER_RIGHT] = &pop_bumper;
	switch_matrix_function[SWITCH_BUMPER_LOWER] = &pop_bumper;

	switch_matrix_function[SWITCH_LEFT_SLINGSHOT] = &sling_shot;
	switch_matrix_function[SWITCH_RIGHT_SLINGSHOT] = &sling_shot;

	switch_matrix_function[SWITCH_RIGHT_SAUCER] = &saucer_sw;
	switch_matrix_function[SWITCH_UPPER_SAUCER] = &saucer_sw;

	switch_matrix_function[SWITCH_MAEL_M] = &mael_lanes;
	switch_matrix_function[SWITCH_MAEL_A] = &mael_lanes;
	switch_matrix_function[SWITCH_MAEL_E] = &mael_lanes;
	switch_matrix_function[SWITCH_MAEL_L] = &mael_lanes;

	switch_matrix_function[SWITCH_RON_R] = &ron_lanes;
	switch_matrix_function[SWITCH_RON_O] = &ron_lanes;
	switch_matrix_function[SWITCH_RON_N] = &ron_lanes;

	switch_matrix_function[SWITCH_UPPER_LEFT_TARGET] = &upper_left_target;
	switch_matrix_function[SWITCH_ALLEY_TARGET_UPPER] = &alley_target_sw;
	switch_matrix_function[SWITCH_CAPTIVE_BALL] = &captive_ball;

	direct_switch_function[SWITCH_LEFT_ACTION_BUTTON] = &action_button;
	direct_switch_function[SWITCH_RIGHT_ACTION_BUTTON] = &action_button;
	direct_switch_function[SWITCH_RIGHT_FLIPPER_BUTTON] = &flipper;
	direct_switch_function[SWITCH_LEFT_FLIPPER_BUTTON] = &flipper;
	direct_switch_function[SWITCH_LOWER_RIGHT_FLIPPER_EOS] = &flipper;
	direct_switch_function[SWITCH_LOWER_LEFT_FLIPPER_EOS] = &flipper;
	direct_switch_function[SWITCH_COIN_DOOR] = &coin_door;
	direct_switch_function[SWITCH_PLUMB_BOB_TILT] = &tilt;

	direct_switch_function[SWITCH_ENTER_BUTTON] = &diagnostics_button;
//	direct_switch_function[SWITCH_UP_BUTTON] = &alley_drop_target;

//	direct_switch_function[SWITCH_DOWN_BUTTON] = &alley_drop_target;
}
