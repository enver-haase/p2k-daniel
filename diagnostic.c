
#include "diagnostic.h"

static SWITCH_FUNCTION switch_matrix_function[0x7f];
static SWITCH_FUNCTION direct_switch_function[0x13f];

SWITCH_FUNCTION* diagnostic_switch_matrix_function(void) {	return switch_matrix_function;}
SWITCH_FUNCTION* diagnostic_direct_switch_function(void) {	return direct_switch_function; }

int solenoid_cnt;

int solenoids[] = {
SOLENOID_MAGNET,
SOLENOID_UPPER_SAUCER,
SOLENOID_RIGHT_SAUCER,
//SOLENOID_ALLEY_TARGET_LOWER_UP,
SOLENOID_AUTO_LAUNCH,
/*SOLENOID_ALLEY_TARGET_LOWER_DOWN,*/
SOLENOID_ALLEY_TARGET_MIDDLE_DOWN,
//SOLENOID_ALLEY_TARGET_MIDDLE_UP,
SOLENOID_DROP_TARGET_BANK,
SOLENOID_THROUGH_EJECT,
SOLENOID_LEFT_SLINGSHOT,
SOLENOID_RIGHT_SLINGSHOT,
SOLENOID_BUMPER_UPPER,
SOLENOID_BUMPER_RIGHT,
SOLENOID_BUMPER_LOWER,
SOLENOID_LOWER_RIGHT_FLIPPER_POWER,
SOLENOID_LOWER_LEFT_FLIPPER_POWER
};

void default_diagnostic_switch_matrix_function(int sw, BYTE state)
{
//	rt_printk("DEFAULT SM sw=%x, state=%d, time=%d\n", sw, state, rt_get_time());
}


void default_diagnostic_direct_switch_function(int sw, BYTE state)
{
//	rt_printk("DEFAULT DS sw=%x, state=%d, time=%d\n", sw, state, rt_get_time());
}


void up_down_buttons(int sw, BYTE state)
{
	if (state == SW_OPEN) {	return;	}

	if (sw == SWITCH_UP_BUTTON) 
	{
		solenoid_cnt++;
		if (solenoid_cnt > 15) solenoid_cnt = 0;
	}
	else
	{
		solenoid_cnt--;
		if (solenoid_cnt < 0) solenoid_cnt = 15;
	}
	rt_printk("up_down_buttons, sw=%x, state=%d, solenoid_cnt=%d\n", sw, state, solenoid_cnt);
}


void enter_button(int sw, BYTE state)
{
	if (state == SW_OPEN) {	return;	}
	rt_printk("enter_button, solenoid_cnt=%d\n", solenoid_cnt);
	fire_solenoid(solenoids[solenoid_cnt], 100);
}


void init_diagnostic(void)
{
	int i;
	for (i = 0; i < 0x7f; i++) switch_matrix_function[i] = &default_diagnostic_switch_matrix_function;
	for (i = 0; i < 0x13f; i++) direct_switch_function[i] = &default_diagnostic_direct_switch_function;

	direct_switch_function[SWITCH_DOWN_BUTTON] = &up_down_buttons;
	direct_switch_function[SWITCH_UP_BUTTON] = &up_down_buttons;
	direct_switch_function[SWITCH_ENTER_BUTTON] = &enter_button;

	solenoid_cnt = 0;
}


void start_diagnostic(void)
{

}

