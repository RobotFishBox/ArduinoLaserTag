/*
 Arduino Laser Tag pin configurations.
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

#ifndef PINS_H
#define PINS_H

#define SD_SEGMENT_PIN_ARRAY {8, 9, 5, 17, 13, 14, 16, 15}   //Pins for the segments on the segment display
#define SD_POWER_PIN_ARRAY {10, 7, 6, 18}                    //Pins for power

#define IR_RECEIVER_PIN 2      //Pin for IR receiver

#define MOTOR_PIN 19
#define TRIGGER_PIN_ANALOG A7
#define RELOAD_PIN_ANALOG A6
#define LEDS_PIN 4

#define SOUND_PIN_1 11
#define SOUND_PIN_2 12

#endif
