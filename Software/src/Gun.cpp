/*
 Laser gun game object
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
   Created as a laser tag game object
 */
 
#include "Gun.h"
#include "Configuration.h"
#include "SoundLibrary.h"

//------------------------------------------------------
// public
//------------------------------------------------------

Gun::Gun (){
  _state = GUN_STATE_IDLE;
  
  _reloadAction = (byte *)actionReload_PGM;
  
  setGunType (GT_HANDGUN, GT_HANDGUN_INIT_AMOUNT, GT_HANDGUN_RELOAD_AMOUNT);
  
  resetInputFlags ();
  resetOutputFlags ();
}

int Gun::getAmmoSupply (){
  return (_ammoSupply);
}

int Gun::getAmmoClip () {
  return (_ammoClip);
}

int Gun::getIRCode () {
  return (_IRCode);
}

int Gun::getState () {
  return (_state);
}
  
boolean Gun::sendIR () {
  return (_sendIR);
}
  
boolean Gun::playSound () {
  return (_playSound);
}
  
byte *Gun::getGunSound () {
  return (_currSound);
}
  
void Gun::setTrigger (boolean value) {
  _trigger = value;
}

void Gun::setReload (boolean value) {
  _reload = value;
}

void Gun::setAmmoSupply (int value) {
  _ammoSupply = value;
}

void Gun::setAmmoClip (int value) {
  _ammoClip = value;
}

void Gun::setGunType (int gunType, int ammoSupply, int ammoClip) {
  _gunType = gunType;
  switch(_gunType) {
  case GT_BOW:
    _triggerAction = (byte *)actionBow_PGM;
    _reloadAmount = GT_BOW_RELOAD_AMOUNT;
    break;
  case GT_HANDGUN:
    _triggerAction = (byte*)actionHandGun_PGM;
    _reloadAmount = GT_HANDGUN_RELOAD_AMOUNT;
    break;
  case GT_SHOTGUN:
    _triggerAction = (byte *)actionShotGun_PGM;
    _reloadAmount = GT_SHOTGUN_RELOAD_AMOUNT;
    break;
  case GT_MACHINE_GUN:
    _triggerAction = (byte *)actionMachineGun_PGM;
    _reloadAmount = GT_MACHINE_GUN_RELOAD_AMOUNT;
    break;
  }
  
  _ammoSupply = ammoSupply;
  _ammoClip = ammoClip;
}

void Gun::setDisabled (boolean value) {
  if (value){
    _state = GUN_STATE_DISABLED;
    resetInputFlags ();
    resetOutputFlags ();
    
  }else if (_state == GUN_STATE_DISABLED && !value) {
    _state = GUN_STATE_IDLE;
  }
}

void Gun::setSoundPlaying (int value) {
  _soundPlaying = value;
}

void Gun::updateGun () {
  switch(_state) {
    case GUN_STATE_IDLE:
     if (_trigger) {
        _state = GUN_STATE_TRIGGER;
        _currAction = _triggerAction;
      } else if (_reload) {
        _state = GUN_STATE_RELOAD;
        _currAction = _reloadAction;
      } else {
        resetOutputFlags ();
      }
      break;
    case GUN_STATE_TRIGGER:
      resetOutputFlags ();
      runAction(pgm_read_byte(_currAction));
      break;
    case GUN_STATE_RELOAD:
      resetOutputFlags ();
      runAction(pgm_read_byte(_currAction));
      break;
    case GUN_STATE_DISABLED:
      setDisabled(true);    //make sure it stays disabled
      break;
  }
}

//------------------------------------------------------
// private
//------------------------------------------------------
void Gun::resetInputFlags (){
    _trigger = false;
    _reload = false;
    _soundPlaying = false;
}

void Gun::resetOutputFlags (){
    _sendIR = false;
    _playSound = false;
}

void Gun::runAction(byte value) {
  switch(value) {
  case ACTION_WAIT_TRIGGER_RELEASE:
    if (!_trigger) {_currAction++;}
    break;
  case ACTION_WAIT_RELOAD_RELEASE:
    if (!_reload) {_currAction++;}
    break;
  case ACTION_WAIT_SOUND_FINISH:
    if (!_soundPlaying) {_currAction++;}
    break;
  case ACTION_CHECK_AMMO:
    _currAction++;
    if (_ammoClip > 0) {
      _ammoClip--;
      _currAction= _currAction + pgm_read_byte(_currAction) + 1;
    } else {
      _currSound = (byte *)soundLibrary_PRG[SOUND_AMMO_EMPTY];
      _playSound = true;
      _currAction++;
    }
    break;
  case ACTION_CHECK_RELOAD_AVAILABLE:
    _currAction++;
    if (_ammoClip == _reloadAmount) {
      _currAction++;
    } else if (_ammoSupply == 0) {
      _currSound = (byte *)soundLibrary_PRG[SOUND_AMMO_EMPTY];
      _playSound = true;
      _currAction++;
    } else {
      int load = _reloadAmount - _ammoClip;
      if (_ammoSupply >= load) {
        _ammoSupply -= load;
        _ammoClip += load;
      } else {
        _ammoClip += _ammoSupply;
        _ammoSupply = 0;
      }
      _currAction= _currAction + pgm_read_byte(_currAction) + 1;
    }
    break;
  case ACTION_CHECK_BOW_RELEASE:
    if (!_trigger) {
      _currAction++;
      if (!_soundPlaying) {
        _currAction= _currAction + pgm_read_byte(_currAction) + 1;
      } else {
        _currSound = (byte *)soundLibrary_PRG[SOUND_STOP];
        _playSound = true;
        _currAction++;
      }
    }
    break;   
  case ACTION_SENDIR:
   _currAction++;
   _IRCode = pgm_read_byte(_currAction++);
   _sendIR = true;
    break;
  case ACTION_PLAY_SOUND:
   _currAction++;
   _currSound = (byte *)soundLibrary_PRG[pgm_read_byte(_currAction++)];
   _playSound = true;
    break;
  case ACTION_RESET:
    _state = GUN_STATE_IDLE;
    break; 
  }
}
