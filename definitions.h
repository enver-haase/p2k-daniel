
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Generic Pinball 2000 definitions
#define REGISTER_SWITCH_COIN        0x00    // 00000000 [0x00]  U2-y0   Input   Coin switches
#define REGISTER_SWITCH_FLIPPER     0x01    // 00000001 [0x01]  U2-y1   Input   Flipper switches
#define REGISTER_SWITCH_DIP         0x02    // 00000010 [0x02]  U2-y2   Input   DIP Switches on driver board
#define REGISTER_SWITCH_MISC        0x03    // 00000011 [0x03]  U2-y3   Input   Flipper EOS and diagnostics
#define REGISTER_SWITCH_ROW         0x04    // 00000100 [0x04]  U2-y4   Input   Switch row receivers
#define REGISTER_SWITCH_COLUMN      0x05    // 00000101 [0x05]  U2-y5   Output  Switch column drivers
#define REGISTER_LAMP_ROW_A         0x06    // 00000110 [0x06]  U2-y6   Output  Lamp set A row drivers
#define REGISTER_LAMP_ROW_B         0x07    // 00000111 [0x07]  U2-y7   Output  Lamp set B row drivers
#define REGISTER_LAMP_COLUMN        0x08    // 00001000 [0x08]  U4-y0   Output  Lamp column drivers
#define REGISTER_SOLENOID_C         0x09    // 00001001 [0x09]  U4-y1   Output  Solenoid set C
#define REGISTER_SOLENOID_B         0x0a    // 00001010 [0x0A]  U4-y2   Output  Solenoid set B
#define REGISTER_SOLENOID_A         0x0b    // 00001011 [0x0B]  U4-y3   Output  Solenoid set A
#define REGISTER_SOLENOID_FLIPPER   0x0c    // 00001100 [0x0C]  U4-y4   Output  Flipper solenoids
#define REGISTER_SOLENOID_D         0x0d    // 00001101 [0x0D]  U4-y5   Output  Solenoid set D
#define REGISTER_SOLENOID_LOGIC     0x0e    // 00001110 [0x0E]  U4-y6   Output  Logic-level drivers
#define REGISTER_SWITCH_ZERO        0x0f    // 00001111 [0x0F]  U4-y7   Input   System info on driver board
#define REGISTER_LAMP_A_DIAGNOSTIC  0x10    // 00010000 [0x10]  U6-y0   Input   Lamp set A diagnostic inputs
#define REGISTER_LAMP_B_DIAGNOSTIC  0x11    // 00010001 [0x11]  U6-y1   Input   Lamp set B diagnostic inputs
#define REGISTER_FUSE_A_DIAGNOSTIC  0x12    // 00010010 [0x12]  U6-y2   Input   Fuse set A diagnostic inputs
#define REGISTER_FUST_B_DIAGNOSTIC  0x13    // 00010011 [0x13]  U6-y3   Input   Fuse set B diagnostic inputs 


// Switch matrix
#define SWITCH_START_BUTTON             0x02
#define SWITCH_MAEL_M            		0x05
#define SWITCH_MAEL_E             		0x06
#define SWITCH_SHOOTER_LANE_LOWER		0x07

#define SWITCH_CAPTIVE_BALL				0x10
#define SWITCH_ALLEY_TARGET_UPPER		0x14
#define SWITCH_MAEL_A             		0x15
#define SWITCH_MAEL_L             		0x16

#define SWITCH_RON_R					0x20
#define SWITCH_RIGH_LOOP_UPPER			0x21
#define SWITCH_SHOOTER_LANE_UPPER		0x22
#define SWITCH_RON_N					0x23
#define SWITCH_LEFT_LOOP_UPPER			0x24
#define SWITCH_RON_O					0x25
//#define SWITCH_ALLEY_TARGET_LOWER		0x26
#define SWITCH_RIGHT_SAUCER				0x27

#define SWITCH_THROUGH_JAM              0x30
#define SWITCH_THROUGH_BALL_1           0x31
#define SWITCH_THROUGH_BALL_2           0x32
#define SWITCH_THROUGH_BALL_3           0x33
#define SWITCH_THROUGH_BALL_4           0x34
#define SWITCH_DROP_TARGET_MIDDLE  		0x35
#define SWITCH_DROP_TARGET_LEFT  		0x36

#define SWITCH_DROP_TARGET_RIGHT  		0x40
//#define SWITCH_CENTER_TARGET_LEFT		0x42
#define SWITCH_CENTER_TARGET			0x43
#define SWITCH_UPPER_SAUCER				0x44
#define SWITCH_SPINNER					0x45

#define SWITCH_LEFT_SLINGSHOT           0x50
#define SWITCH_RIGHT_SLINGSHOT          0x51
#define SWITCH_BUMPER_LOWER				0x52
#define SWITCH_BUMPER_RIGHT				0x53
#define SWITCH_BUMPER_UPPER				0x54
#define SWITCH_ALLEY_TARGET_MIDDLE		0x55
#define SWITCH_UPPER_LEFT_TARGET		0x56
#define SWITCH_LEFT_LOOP_LOWER			0x57



// Coin slot switches (REGISTER_SWITCH_COIN)
#define SWITCH_COIN_1                   0x00
#define SWITCH_COIN_2                   0x01
#define SWITCH_COIN_3                   0x02
#define SWITCH_COIN_4                   0x03
#define SWITCH_COIN_5                   0x04
#define SWITCH_COIN_6                   0x05
#define SWITCH_COIN_7                   0x06
#define SWITCH_COIN_8                   0x07

// Cabinet flipper switches (REGISTER_SWITCH_FLIPPER)
#define SWITCH_SLAM_TILT                0x10
#define SWITCH_COIN_DOOR		        0x11
#define SWITCH_PLUMB_BOB_TILT           0x12
#define SWITCH_RIGHT_FLIPPER_BUTTON     0x14
#define SWITCH_LEFT_FLIPPER_BUTTON      0x15
#define SWITCH_RIGHT_ACTION_BUTTON      0x16
#define SWITCH_LEFT_ACTION_BUTTON       0x17

// Dip switches (REGISTER_SWITCH_DIP)
#define SWITCH_DIP_1   			        0x20
#define SWITCH_DIP_2   			        0x21
#define SWITCH_DIP_3   			        0x22
#define SWITCH_DIP_4   			        0x23

// Diagnostic switches & Playfield flipper switches (E.O.S) (REGISTER_SWITCH_MISC)
#define SWITCH_ESCAPE_BUTTON            0x30
#define SWITCH_DOWN_BUTTON              0x31
#define SWITCH_UP_BUTTON                0x32
#define SWITCH_ENTER_BUTTON             0x33
#define SWITCH_LOWER_RIGHT_FLIPPER_EOS  0x34
#define SWITCH_LOWER_LEFT_FLIPPER_EOS   0x35
#define SWITCH_UPPER_RIGHT_FLIPPER_EOS  0x36
#define SWITCH_UPPER_LEFT_FLIPPER_EOS   0x37

// Zero switches (REGISTER_SWITCH_ZERO)
#define SWITCH_TIX_NOC 			        0xf4
#define SWITCH_TIX_LOW 			        0xf5
#define SWITCH_BLANKING			        0xf6
#define SWITCH_ZERO_SI 			        0xf7

// Fuse test A (REGISTER_FUSE_A_DIAGNOSTIC)
#define FUSE_F104						0x120
#define FUSE_F105						0x121
#define FUSE_F106						0x122
#define FUSE_F107						0x123
#define FUSE_F103						0x124
#define FUSE_F102						0x125
#define FUSE_F101						0x126
#define FUSE_F100						0x127

// Fuse test B (REGISTER_FUSE_B_DIAGNOSTIC)
#define FUSE_F109						0x130
#define FUSE_F110						0x131
#define FUSE_F112						0x132
#define FUSE_F111						0x133


// Solenoids 1 - 8 (REGISTER_SOLENOID_A)

#define SOLENOID_DROP_TARGET_BANK          	0xb0
//#define SOLENOID_ALLEY_TARGET_MIDDLE_UP		0xb1
//#define SOLENOID_ALLEY_TARGET_LOWER_DOWN	0xb2
#define SOLENOID_AUTO_LAUNCH				0xb2
#define SOLENOID_MAGNET                     0xb3
#define SOLENOID_KICKBACK                   0xb6
#define SOLENOID_ALLEY_TARGET_MIDDLE_DOWN   0xb5
//#define SOLENOID_ALLEY_TARGET_LOWER_UP     	0xb6
#define SOLENOID_UPPER_SAUCER               0xb7

// Solenoids 9 - 16 (REGISTER_SOLENOID_B)
#define SOLENOID_THROUGH_EJECT              0xa0
#define SOLENOID_LEFT_SLINGSHOT             0xa1
#define SOLENOID_RIGHT_SLINGSHOT            0xa2
#define SOLENOID_RIGHT_SAUCER               0xa3
#define SOLENOID_BUMPER_LOWER           	0xa4
#define SOLENOID_BUMPER_UPPER           	0xa5
//#define SOLENOID_AUTO_LAUNCH		        0xa7
#define SOLENOID_BUMPER_RIGHT          		0xa7

// Solenoids 17 - 24 (REGISTER_SOLENOID_C)  0x90
#define FLASHER_BACK_PANEL_5      			0x92
#define FLASHER_BACK_PANEL_7     			0x93 
#define FLASHER_BACK_PANEL_4           		0x97 

// Solenoids 25 - 32 (REGISTER_SOLENOID_D)
#define FLASHER_BACK_PANEL_6      			0xd0
#define FLASHER_BACK_PANEL_3       			0xd1
#define FLASHER_BACK_PANEL_1      			0xd2
#define FLASHER_BACK_PANEL_2		        0xd3

// Solenoids 25 - 32 (REGISTER_SOLENOID_D)
#define HEALTH_LED							0xd4
#define INTER_LOCK_RELAY					0xd5
#define COUNTER								0xd6
#define LAMP_TEST_CONTROL					0xd7

// Solenoids 33 - 40 (REGISTER_SOLENOID_FLIPPER)
#define SOLENOID_LOWER_RIGHT_FLIPPER_POWER  0xc0
#define SOLENOID_LOWER_RIGHT_FLIPPER_HOLD   0xc1
#define SOLENOID_LOWER_LEFT_FLIPPER_POWER   0xc2
#define SOLENOID_LOWER_LEFT_FLIPPER_HOLD    0xc3

// Solenoids 41 - 48 (REGISTER_SOLENOID_LOGIC) 0xe0
#define DISCO_BALL_MOTOR                    0xe0


// Lamp matrix A
#define LAMP_START_BUTTON                   0x02
#define LAMP_RON_N							0x04
#define LAMP_RON_O							0x05
#define LAMP_RON_R							0x06

#define LAMP_TICKETS_LOW                    0x10
#define LAMP_COIN_DOOR_ILLUMINATION         0x13
#define LAMP_TARGET_UPPER_CENTER			0x14
#define LAMP_JACKPOT_CENTER_LEFT			0x15
#define LAMP_JACKPOT_CENTER_RIGHT			0x16
#define LAMP_JACKPOT_UPPER_CENTER			0x17

#define LAMP_CAPTIVE_BALL					0x24
#define LAMP_LEFT_LOOP						0x25
#define LAMP_JACKPOT_LEFT_LOOP				0x26
#define LAMP_ALLEY_TARGET				0x27

#define LAMP_SPARKS_K						0x30
#define LAMP_SPARKS_S2						0x31
#define LAMP_JACKPOT_RIGHT_HOLE				0x32
#define LAMP_EXTRA_BALL						0x33
#define LAMP_SPARKS_S1						0x34
#define LAMP_SPARKS_P						0x35
#define LAMP_SPARKS_R						0x36
#define LAMP_SPARKS_A						0x37

#define LAMP_SHOOTER_LANE_4					0x40
#define LAMP_DROP_TARGET_RIGHT				0x41
#define LAMP_DROP_TARGET_LEFT				0x42
#define LAMP_RIGHT_LOOP						0x43
#define LAMP_SHOOTER_LANE_5					0x44
#define LAMP_SHOOTER_LANE_3					0x45
#define LAMP_JACKPOT_RIGHT_LOOP				0x46
#define LAMP_DROP_TARGET_MIDDLE				0x47

#define LAMP_BUMPER_LEFT					0x50
#define LAMP_MAEL_L			                0x51
#define LAMP_BUMPER_LOWER					0x52
#define LAMP_MAEL_E		                    0x53
#define LAMP_SHOOTER_LANE_1					0x54
#define LAMP_BUMPER_RIGHT					0x55
#define LAMP_SHOOTER_LANE_2					0x56
#define LAMP_UPPER_LEFT_SPOTLIGHT			0x57


#define LAMP_RUSSELL_L1		                0x60
#define LAMP_RUSSELL_S2		                0x61
#define LAMP_RUSSELL_R		                0x62
#define LAMP_RUSSELL_L2		                0x63
#define LAMP_RIGHT_SPOTLIGHT                0x64
#define LAMP_RUSSELL_E		                0x65
#define LAMP_RUSSELL_S1		                0x66
#define LAMP_RUSSELL_U		                0x67

#define LAMP_LOWER_LEFT_SPOTLIGHT          	0x70
#define LAMP_MAEL_M		                  	0x72
#define LAMP_SHOOT_AGAIN                    0x74
#define LAMP_MAEL_A		                   	0x75
#define LAMP_KICKBACK		                0x76
#define LAMP_ALLEY_ENTRANCE					0x77


// Lamp matrix B (starts on 0x80)


// Events to user space program
#define KERNEL_EVENT_SPINNER_ON				0
#define KERNEL_EVENT_SPINNER_OFF			1
#define KERNEL_EVENT_RIGHT_HOLE				2
#define KERNEL_EVENT_UPPER_HOLE				4
#define KERNEL_EVENT_LEFT_DROPTARGET_BANK	5
#define KERNEL_EVENT_MIDDLE_DROPTARGET_BANK	6
#define KERNEL_EVENT_RIGHT_DROPTARGET_BANK	7
#define KERNEL_EVENT_ALL_DROPTARGET_BANK	8
#define KERNEL_EVENT_CAPTIVE_BALL			11
#define KERNEL_EVENT_BUMPER_HIT				12
#define KERNEL_EVENT_CENTER_TARGET			13
#define KERNEL_EVENT_ALLEY_TARGET_UPPER		14
#define KERNEL_EVENT_UPPER_LEFT_TARGET		15
#define KERNEL_EVENT_KICKBACK_FIRED			16
#define KERNEL_EVENT_RON_SWITCH				17
#define KERNEL_EVENT_TILT					18
#define KERNEL_EVENT_ALLEY_TARGET_LOWER		19
#define KERNEL_EVENT_MAEL_SWITCH			20
#define KERNEL_EVENT_LEFT_LOOP				21
#define KERNEL_EVENT_SLING_SHOT				22


#define KERNEL_EVENT_MULTIBALL				1000
#define KERNEL_EVENT_RON_SPELLED			1001
#define KERNEL_EVENT_MAEL_SPELLED			1002
#define KERNEL_EVENT_KICKBACK_LIT			1003
#define KERNEL_EVENT_GAME_INITIALIZED		1004
#define KERNEL_EVENT_GAME_STARTED			1005
#define KERNEL_EVENT_PLAYER_ADDED			1006
#define KERNEL_EVENT_JACKPOT				1007
#define KERNEL_EVENT_JACKPOT_UPPER_LEFT		1008
#define KERNEL_EVENT_SUPER_JACKPOT			1009
#define KERNEL_EVENT_SUPER_DUPER_JACKPOT	1010

#define KERNEL_EVENT_S						1010
#define KERNEL_EVENT_P						1011
#define KERNEL_EVENT_A						1012
#define KERNEL_EVENT_R						1013
#define KERNEL_EVENT_K						1014
#define KERNEL_EVENT_SPARKS_SPELLED			1015

#define KERNEL_EVENT_SUPER_JACKPOT_1		1016
#define KERNEL_EVENT_SUPER_JACKPOT_2		1017

// Events from user space program
#define USERSPACE_EVENT_RELEASE_UPPER_HOLE		2000
#define USERSPACE_EVENT_RELEASE_RIGHT_HOLE		2001



#endif
