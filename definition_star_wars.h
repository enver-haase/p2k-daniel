
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
#define SWITCH_LEFT_DROP_TARGET         0x04
#define SWITCH_LEFT_OUTLANE             0x05
#define SWITCH_RIGHT_INLANE             0x06
#define SWITCH_SHOOTER_LANE             0x07

#define SWITCH_CAPTIVE_BALL             0x10
#define SWITCH_RIGHT_DROP_TARGET        0x14
#define SWITCH_LEFT_INLANE              0x15
#define SWITCH_RIGHT_OUTLANE            0x16
#define SWITCH_SNEAKY_LANE              0x17

#define SWITCH_RIGHT_BANK_UPPER         0x20
#define SWITCH_RIGHT_BANK_MIDDLE        0x21
#define SWITCH_RIGHT_BANK_LOWER         0x22
#define SWITCH_LEFT_BANK_UPPER          0x23
#define SWITCH_LEFT_BANK_MIDDLE         0x24
#define SWITCH_LEFT_BANK_LOWER          0x25
#define SWITCH_LEFT_SAUCER              0x26
#define SWITCH_RIGHT_SAUCER             0x27

#define SWITCH_THROUGH_JAM              0x30
#define SWITCH_THROUGH_BALL_1           0x31
#define SWITCH_THROUGH_BALL_2           0x32
#define SWITCH_THROUGH_BALL_3           0x33
#define SWITCH_THROUGH_BALL_4           0x34
#define SWITCH_LEFT_RAMP_ENTER          0x35
#define SWITCH_RIGHT_RAMP_ENTER         0x36

#define SWITCH_SHIELD_POPPER            0x40
#define SWITCH_LEFT_SHIELD_TARGET       0x42
#define SWITCH_RIGHT_SHIELD_TARGET      0x43
#define SWITCH_RAMP_MADE_LEFT           0x44
#define SWITCH_RAMP_MADE_RIGHT          0x45
#define SWITCH_SHIELD_UP                0x46
#define SWITCH_SHIELD_HIT               0x47

#define SWITCH_LEFT_SLINGSHOT           0x50
#define SWITCH_RIGHT_SLINGSHOT          0x51
#define SWITCH_UPPER_JET_BUMPER         0x52
#define SWITCH_MIDDLE_JET_BUMPER        0x53
#define SWITCH_LOWER_JET_BUMPER         0x54
#define SWITCH_JETS_ROLLOVER            0x55
#define SWITCH_LEFT_LOOP_UPPER          0x56
#define SWITCH_LEFT_LOOP_ROLLOVER       0x57


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
#define SOLENOID_LEFT_SAUCER                0xb0
#define SOLENOID_LEFT_DROP_TARGET_UP        0xb1
#define SOLENOID_LEFT_DROP_TARGET_DOWN      0xb2
#define SOLENOID_MAGNET                     0xb3
#define SOLENOID_RIGHT_DROP_TARGET_DOWN     0xb5
#define SOLENOID_RIGHT_DROP_TARGET_UP       0xb6
#define SOLENOID_SHIELD_POPPER              0xb7

// Solenoids 9 - 16 (REGISTER_SOLENOID_B)
#define SOLENOID_THROUGH_EJECT              0xa0
#define SOLENOID_LEFT_SLINGSHOT             0xa1
#define SOLENOID_RIGHT_SLINGSHOT            0xa2
#define SOLENOID_UPPER_JET_BUMPER           0xa3
#define SOLENOID_MIDDLE_JET_BUMPER          0xa4
#define SOLENOID_LOWER_JET_BUMPER           0xa5
#define FLASHER_UPPER_HOTDOG                0xa6
#define SOLENOID_RIGHT_SAUCER               0xa7

// Solenoids 17 - 24 (REGISTER_SOLENOID_C)
#define FLASHER_LOWER_LEFT_HOTDOG           0x90
#define FLASHER_LOWER_RIGHT_HOTDOG          0x91
#define FLASHER_BACK_PANEL_RIGHT_UPPER      0x92
#define FLASHER_BACK_PANEL_RIGHT_MIDDLE     0x93
#define FLASHER_JET                         0x94
#define FLASHER_LEFT_INLANE                 0x95
#define FLASHER_RIGHT_INLANE                0x96
#define FLASHER_BACK_PANEL_MIDDLE           0x97

// Solenoids 25 - 32 (REGISTER_SOLENOID_D)
#define FLASHER_BACK_PANEL_RIGHT_LOWER      0xd0
#define FLASHER_BACK_PANEL_LEFT_UPPER       0xd1
#define FLASHER_BACK_PANEL_LEFT_MIDDLE      0xd2
#define FLASHER_BACK_PANEL_LEFT_LOWER       0xd3
#define HEALTH_LED							0xd4
#define INTER_LOCK_RELAY					0xd5
#define COUNTER								0xd6
#define LAMP_TEST_CONTROL					0xd7

// Solenoids 33 - 40 (REGISTER_SOLENOID_FLIPPER)
#define SOLENOID_LOWER_RIGHT_FLIPPER_POWER  0xc0
#define SOLENOID_LOWER_RIGHT_FLIPPER_HOLD   0xc1
#define SOLENOID_LOWER_LEFT_FLIPPER_POWER   0xc2
#define SOLENOID_LOWER_LEFT_FLIPPER_HOLD    0xc3
#define SOLENOID_CENTER_BUMPER_POWER        0xc4
#define SOLENOID_CENTER_BUMPER_HOLD         0xc5
#define FLASHER_LEFT_LASER                  0xc6
#define FLASHER_RIGHT_LASER                 0xc7

// Solenoids 41 - 48 (REGISTER_SOLENOID_LOGIC)
#define NEON_SABER                          0xe0


// Lamp matrix A
#define LAMP_START_BUTTON                   0x02
#define LAMP_SHIELD_LOWER_RIGHT             0x04
#define LAMP_SHIELD_LOWER_4                 0x05
#define LAMP_SHIELD_LOWER_3                 0x06
#define LAMP_SHIELD_LOWER_2                 0x07

#define LAMP_TICKETS_LOW                    0x10
#define LAMP_COIN_DOOR_ILLUMINATION         0x13
#define LAMP_SHIELD_MIDDLE_RIGHT            0x14
#define LAMP_SHIELD_MIDDLE_3                0x15
#define LAMP_SHIELD_MIDDLE_2                0x16
#define LAMP_SHIELD_LOWER_LEFT              0x17

#define LAMP_SHIELD_UPPER_RIGHT             0x24
#define LAMP_SHIELD_UPPER_MIDDLE            0x25
#define LAMP_SHIELD_MIDDLE_LEFT             0x26
#define LAMP_SHIELD_UPPER_LEFT              0x27

#define LAMP_LEFT_LOOP_RIGHT_LEG            0x30
#define LAMP_LEFT_LOOP_RIGHT_FOOT           0x31
#define LAMP_LEFT_LOOP_LEFT_FOOT            0x32
#define LAMP_LEFT_LOOP_LEFT_LEG             0x33
#define LAMP_JEDI_E                         0x34
#define LAMP_JEDI_J                         0x35
#define LAMP_JEDI_I                         0x36
#define LAMP_JEDI_D                         0x37

#define LAMP_LEFT_LOOP_BODY_MIDDLE          0x40
#define LAMP_LEFT_LOOP_BODY_UPPER           0x41
#define LAMP_LEFT_LOOP_HEAD                 0x42
#define LAMP_LEFT_LOOP_BODY_LOWER           0x43
#define LAMP_RIGHT_RAMP_GI                  0x44
#define LAMP_SCOOP_LOWER_RIGHT_GI           0x45
#define LAMP_LEFT_LOOP_ROLLOVER             0x46
#define LAMP_LEFT_SAUCER                    0x47

#define LAMP_RIGHT_STANDUP_UPPER            0x50
#define LAMP_RIGHT_STANDUP_MIDDLE           0x51
#define LAMP_RIGHT_STANDUP_LOWER            0x52
#define LAMP_LEFT_STANDUP_LOWER             0x53
#define LAMP_LEFT_STANDUP_MIDDLE            0x54
#define LAMP_LEFT_STANDUP_UPPER             0x55

#define LAMP_BOTTOM_ARCH_LEFT_LEFT          0x60
#define LAMP_LEFT_INLANE_GI_RIGHT           0x61
#define LAMP_LEFT_SLINGSHOT_GI_UPPER        0x62
#define LAMP_LEFT_LOOP_LOWER_GI             0x63
#define LAMP_CAPTIVE_BALL_GI                0x64
#define LAMP_SCOOP_LOWER_LEFT_GI            0x65
#define LAMP_SCOOP_UPPER_LEFT_GI            0x66
#define LAMP_JET_TOP_GI                     0x67

#define LAMP_BOTTOM_ARCH_RIGHT_RIGHT        0x70
#define LAMP_RIGHT_INLANE_GI_LEFT           0x71
#define LAMP_RIGHT_SLINGSHOT_GI_UPPER       0x72
#define LAMP_SHOOTER_RAMP_GI_LOWER          0x73
#define LAMP_SHOOTER_RAMP_GI_MIDDLE         0x74
#define LAMP_RIGHT_STANDUP_GI               0x75
#define LAMP_MIDDLE_JET                     0x76
#define LAMP_JET_MIDDLE_GI                  0x77

// Lamp matrix B
#define LAMP_SHIP_RIGHT_WING_UPPER          0x80
#define LAMP_SHIP_RIGHT_WING_LOWER          0x81
#define LAMP_BONUS_X5                       0x82
#define LAMP_SHIP_TAIL_UPPER                0x83
#define LAMP_JEDI_SPIRIT                    0x84
#define LAMP_RIGHT_HOTDOG_LEFT              0x85
#define LAMP_JETS_ROLLOVER                  0x86
#define LAMP_RIGHT_LASER_END                0x87

#define LAMP_SHIP_BODY_UPPER_RIGHT          0x90
#define LAMP_SHIP_BODY_MIDDLE               0x91
#define LAMP_SHIP_BODY_LOWER                0x92
#define LAMP_BONUS_X4                       0x93
#define LAMP_JEDI_MASTER                    0x94
#define LAMP_FIRE_LASERS_RIGHT              0x95
#define LAMP_RIGHT_SAUCER                   0x96
#define LAMP_EXTRA_BALL                     0x97

#define LAMP_SHIP_LEFT_WING_UPPER           0xA0
#define LAMP_SHIP_LEFT_WING_LOWER           0xA1
#define LAMP_BONUS_X2                       0xA2
#define LAMP_BONUS_X3                       0xA3
#define LAMP_JEDI_YOUTH                     0xA4
#define LAMP_LEFT_HOTDOG_RIGHT              0xA5
#define LAMP_SHOOTER                        0xA6
#define LAMP_BOTTOM_ARCH_RIGHT_LEFT         0xA7

#define LAMP_SHIP_BODY_UPPER_LEFT           0xB0
#define LAMP_SPOTLIGHT_RIGHT                0xB3
#define LAMP_FIRE_LASERS_LEFT               0xB4
#define LAMP_JEDI_KNIGHT                    0xB5
#define LAMP_SHOOT_AGAIN                    0xB6
#define LAMP_LEFT_FLIPPER                   0xB7

#define LAMP_LEFT_LASER_END                 0xC0
#define LAMP_LEFT_SAUCER_INSERT             0xC1
#define LAMP_RIGHT_SAUCER_INSERT            0xC2
#define LAMP_SPOTLIGHT_LEFT                 0xC3
#define LAMP_LEFT_HOTDOG_LEFT               0xC4
#define LAMP_RIGHT_HOTDOG_RIGHT             0xC5
#define LAMP_RIGHT_FLIPPER                  0xC6
#define LAMP_SHIP_TAIL_LOWER                0xC7

#define LAMP_BOTTOM_ARCH_LEFT_RIGHT         0xE0
#define LAMP_LEFT_INLANE_GI_LEFT            0xE1
#define LAMP_LEFT_SLINGSHOT_GI_LOWER        0xE2
#define LAMP_LEFT_OUTLANE_GI                0xE3
#define LAMP_LEFT_STANDUP_GI                0xE4
#define LAMP_LEFT_LOOP_MIDDLE_GI            0xE5
#define LAMP_UPPER_LEFT_CORNER_GI           0xE6
#define LAMP_LEFT_RAMP_GI                   0xE7

#define LAMP_SCOOP_UPPER_RIGHT_GI           0xF0
#define LAMP_UPPER_RIGHT_CORNER_GI          0xF1
#define LAMP_UPPER_JET                      0xF2
#define LAMP_LEFT_LOWER_JET                 0xF3
#define LAMP_SHOOTER_RAMP_GI_UPPER          0xF4
#define LAMP_RIGHT_OUTLANE_GI               0xF5
#define LAMP_RIGHT_SLINGSHOT_GI_LOWER       0xF6
#define LAMP_RIGHT_INLANE_GI_RIGHT          0xF7

#endif
