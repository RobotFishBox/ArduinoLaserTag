/*
 Game gun controls
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
 
#ifndef Gun_h
#define Gun_h

#include "arduino.h"
#include "SoundLibrary.h"
#include "Configuration.h"

//------------------------------------------------------
// actions
//------------------------------------------------------
const PROGMEM byte actionReload_PGM[] = {
  ACTION_CHECK_RELOAD_AVAILABLE, 2, ACTION_WAIT_RELOAD_RELEASE, ACTION_RESET, 
  ACTION_PLAY_SOUND, SOUND_RELOAD_GUN, 
  ACTION_WAIT_RELOAD_RELEASE, 
  ACTION_RESET
};
const PROGMEM byte actionBow_PGM[] = {
  ACTION_PLAY_SOUND, SOUND_BOW_LOAD,
  ACTION_CHECK_BOW_RELEASE, 1, ACTION_RESET, 
  ACTION_SENDIR, IRCODE_BOW,
  ACTION_PLAY_SOUND, SOUND_BOW_RELEASE,
  ACTION_RESET
};
const PROGMEM byte actionHandGun_PGM[] = {
  ACTION_CHECK_AMMO, 2, ACTION_WAIT_TRIGGER_RELEASE, ACTION_RESET,  
  ACTION_SENDIR, IRCODE_HANDGUN, 
  ACTION_PLAY_SOUND, SOUND_HANDGUN_SHOOT, 
  ACTION_WAIT_TRIGGER_RELEASE, 
  ACTION_RESET
};
const PROGMEM byte actionShotGun_PGM[] = {
  ACTION_CHECK_AMMO, 2, ACTION_WAIT_TRIGGER_RELEASE, ACTION_RESET,  
  ACTION_SENDIR, IRCODE_SHOTGUN,
  ACTION_PLAY_SOUND, SOUND_SHOTGUN_SHOOT,
  ACTION_WAIT_SOUND_FINISH,
  ACTION_WAIT_TRIGGER_RELEASE, 
  ACTION_RESET
};
const PROGMEM byte actionMachineGun_PGM[] = {
  ACTION_CHECK_AMMO, 2, ACTION_WAIT_TRIGGER_RELEASE, ACTION_RESET,   
  ACTION_SENDIR, IRCODE_MACHINE_GUN,
  ACTION_PLAY_SOUND, SOUND_MACHINE_GUN_SHOOT,
  ACTION_WAIT_SOUND_FINISH,
  ACTION_RESET
};

//------------------------------------------------------
// gun types setings
//------------------------------------------------------

class Gun
{

public:
  Gun ();
  int getAmmoSupply ();
  int getAmmoClip ();
  int getIRCode ();
  int getState ();
  
  boolean sendIR ();
  boolean playSound ();
  
  byte *getGunSound ();
  
  void setTrigger (boolean value);
  void setReload (boolean value);
  void setAmmoSupply (int value);
  void setAmmoClip (int value);
  void setGunType (int gunType, int ammoSupply, int ammoClip);
  void setDisabled (boolean value);
  void setSoundPlaying (int value);
  void updateGun ();
  
private:
  int _ammoSupply;
  int _ammoClip; 
  int _reloadAmount;
  int _gunType;
  int _IRCode;
  int _state;
  
  boolean _trigger;           //state of the trigger 
  boolean _reload;            //state of reload
  boolean _sendIR;            //send IR signal
  boolean _playSound;
  boolean _soundPlaying;      //used for waiting for sound to finish.
  
  byte *_currAction;
  byte *_reloadAction;
  byte *_triggerAction;
  byte *_currSound;
  
  void resetInputFlags ();
  void resetOutputFlags ();
  void runAction(byte value);
};

#endif
