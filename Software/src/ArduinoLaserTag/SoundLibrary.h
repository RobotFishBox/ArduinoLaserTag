/*
 Sound library for all in game sounds
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

/*
  Decoding sound codes
  
  0xa0  - motor off
  0xa1  - motor on
  
  0xb0  - setup programed tune chanel 0 (start frequency, modifier in percentage)
  0xb1  - setup programed tune chanel 1 (start frequency, modifier in percentage)
  
  0xc0  - play programed tune chanel 0
  0xc1  - play programed tune chanel 1
  
  0xd0  - go back to (numder of codes to go back to)
  0xd1  - start repeat (times to repeat)
*/

#ifndef SOUND_LIBRARY_H
#define SOUND_LIBRARY_H

#include "arduino.h"

#define SOUND_RELOAD_GUN            0
#define SOUND_BOW_LOAD              1
#define SOUND_BOW_RELEASE           2
#define SOUND_HANDGUN_SHOOT         3
#define SOUND_SHOTGUN_SHOOT         4
#define SOUND_MACHINE_GUN_SHOOT     5
#define SOUND_AMMO_EMPTY            6
#define SOUND_SECRET                7
#define SOUND_STOP                  8
#define SOUND_WOUNDED               9

//------------------------------------------------------
// Library sounds
//------------------------------------------------------

const PROGMEM byte soundReloadGun_PRG [] = {
  0xa0, 0xb0, 5, 115, 0xb1, 15, 115, 0xd1, 30, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa1, 
  0xd1, 10, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa0, 0x80, 0x81, 0xf0
};
const PROGMEM byte soundBowLoad_PRG [] = {
  0xa0, 0xb0, 5, 107, 0xb1, 10, 105, 0xd1, 60, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa1, 
  0xd1, 10, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa0, 0x80, 0x81, 0xf0
};
const PROGMEM byte soundBowRelease_PRG [] = {
  0xa0, 0xb0, 105, 98, 0xb1, 110, 90, 0xa1, 0xd1, 10, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa0, 
  0xd1, 30, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0x80, 0x81, 0xf0
};
const PROGMEM byte soundHandgunShoot_PRG [] = {
  0xa0, 0xb0, 100, 95, 0xb1, 120, 95, 0xa1, 0xd1, 10, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa0, 
  0xd1, 20, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0x80, 0x81, 0, 100, 0xf0
};
const PROGMEM byte soundShotgunShoot_PRG [] = {
  0xa0, 0xb0, 90, 99, 0xb1, 100, 90, 0xa1, 0xd1, 30, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa0, 
  0xd1, 50, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0x80, 0x81, 0xf0
};

const PROGMEM byte soundMachineGunShoot_PRG [] = {
  0xa0, 0xb0, 100, 95, 0xb1, 120, 95, 0xa1, 0xd1, 5, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0xa0, 
  0xd1, 5, 0xc0, 0, 10, 0xc1, 0xd0, 5, 0x80, 0x81, 0xf0
};

const PROGMEM byte soundAmmoEmpty_PRG [] = {
  0xa0, 0xb0, 80, 99, 0xb1, 90, 99, 0xd1, 10, 0xc0, 0, 10, 0xc1, 0xd0, 5, 
  0x80, 0x81, 0xf0
};
const PROGMEM byte soundSecret_PRG [] = {
0x90,79, 0,165, 0x91,78, 0,55, 0x80, 0,110, 0x90,75, 0,55, 0x81, 0,110, 0x91,69, 0,55, 
0x80, 0,110, 0x90,68, 0,55, 0x81, 0,110, 0x91,76, 0,55, 0x80, 0,110, 0x90,80, 0,55, 
0x81, 0,110, 0x91,84, 0,55, 0x80, 2,95, 0x81, 0xf0};

const PROGMEM byte soundStop_PRG [] = {
0xa0, 0x80, 0x81, 0xf0};

static const byte* soundLibrary_PRG[] = {
  soundReloadGun_PRG,
  soundBowLoad_PRG,
  soundBowRelease_PRG,
  soundHandgunShoot_PRG,
  soundShotgunShoot_PRG,
  soundMachineGunShoot_PRG, 
  soundAmmoEmpty_PRG,
  soundSecret_PRG,
  soundStop_PRG,
  soundAmmoEmpty_PRG
};


#endif
