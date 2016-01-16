/*
 Configurations for Arduino Laser tag
 Copyright (C) 2015 Anderson Li / http://therobotfish.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Largest number of digits in the segment display being used
#define MAX_SEGMENT_DISPLAY_DIGITS 4

//------------------------------------------------------
// IR constants
//------------------------------------------------------
#define IR_BITS 3      //used to be 32. This was way too long. At most I need is 8 values.
#define IRCODE_BOW                      0
#define IRCODE_HANDGUN                  1
#define IRCODE_SHOTGUN                  2
#define IRCODE_MACHINE_GUN              3

//------------------------------------------------------
// hardware constants
//------------------------------------------------------
#define TRIGGER_THRESHOLD                250
#define RELOAD_THRESHOLD                 250
#define DEBOUNCE_COUNT                   16                 

//------------------------------------------------------
// gun type constants
//------------------------------------------------------
#define GT_NUM_GUNS                      4

#define GT_BOW                          0
#define GT_HANDGUN                      1
#define GT_SHOTGUN                      2
#define GT_MACHINE_GUN                  3

#define GT_BOW_RELOAD_AMOUNT            0
#define GT_HANDGUN_RELOAD_AMOUNT        15
#define GT_SHOTGUN_RELOAD_AMOUNT        6
#define GT_MACHINE_GUN_RELOAD_AMOUNT    50

#define GT_BOW_INIT_AMOUNT              0
#define GT_HANDGUN_INIT_AMOUNT          100
#define GT_SHOTGUN_INIT_AMOUNT          20
#define GT_MACHINE_GUN_INIT_AMOUNT      300

//------------------------------------------------------
// player states constants
//------------------------------------------------------
#define PLAYER_STATE_DISABLED           0
#define PLAYER_STATE_ALIVE              1
#define PLAYER_STATE_DEAD               2
#define PLAYER_STATE_WOUNDED            3

//------------------------------------------------------
// gun states constants
//------------------------------------------------------
#define GUN_STATE_DISABLED              0
#define GUN_STATE_IDLE                  1
#define GUN_STATE_TRIGGER               2
#define GUN_STATE_RELOAD                3

//------------------------------------------------------
// gun action constants
//------------------------------------------------------
#define ACTION_WAIT_TRIGGER_RELEASE           1
#define ACTION_WAIT_SOUND_FINISH              2
#define ACTION_WAIT_RELOAD_RELEASE            3
#define ACTION_CHECK_AMMO                     4
#define ACTION_CHECK_RELOAD_AVAILABLE         5
#define ACTION_CHECK_BOW_RELEASE              6
#define ACTION_SENDIR                         7
#define ACTION_PLAY_SOUND                     8
#define ACTION_RESET                          9

//------------------------------------------------------
// segment display
//------------------------------------------------------
#define SEGMENT_DISPLAY_A   11
#define SEGMENT_DISPLAY_B   8
#define SEGMENT_DISPLAY_C   12
#define SEGMENT_DISPLAY_E   13
#define SEGMENT_DISPLAY_F   14
#define SEGMENT_DISPLAY_G   15
#define SEGMENT_DISPLAY_H   16
#define SEGMENT_DISPLAY_I   1
#define SEGMENT_DISPLAY_J   17
#define SEGMENT_DISPLAY_L   18
#define SEGMENT_DISPLAY_N   19
#define SEGMENT_DISPLAY_P   20
#define SEGMENT_DISPLAY_S   21
#define SEGMENT_DISPLAY_U   22
#define SEGMENT_DISPLAY_O   0
#endif
