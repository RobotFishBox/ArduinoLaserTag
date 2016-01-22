/*
 Laser player game object
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
 
#include "Player.h"
#include "Configuration.h"
#include "SoundLibrary.h"

//------------------------------------------------------
// public
//------------------------------------------------------
Player::Player (){
  _state = PLAYER_STATE_ALIVE;
  _playSound = false;
}

int Player::getState(){
  return(_state);
}

int Player::getHealth (){
  return(_health);
}

boolean Player::playSound (){
  return(_playSound);
}

byte *Player::getSound (){
  return(_currSound);
}

void Player::setIsHit (boolean value){
  _isHit = value;
}

void Player::setIRCode (unsigned long value){
  _irCode = value;
}

void Player::updatePlayer () {
  switch(_state) {
    case PLAYER_STATE_ALIVE:
      break;
  }
}

//------------------------------------------------------
// private
//------------------------------------------------------

void Player::resetInputFlags (){
  _isHit = false;
  _soundPlaying = false;
}

void Player::resetOutputFlags (){
  _playSound = false;
}

void Player::runAction(byte value) {
  switch(value) {
  case ACTION_PLAY_SOUND:
   _currAction++;
   _currSound = (byte *)soundLibrary_PRG[pgm_read_byte(_currAction++)];
   _playSound = true;
    break;
  case ACTION_WAIT_SOUND_FINISH:
    if (!_soundPlaying) {_currAction++;}
    break;
  case ACTION_RESET:
    if(_health <= 0){
      _state = PLAYER_STATE_DEAD;
    } else {
      _state = PLAYER_STATE_ALIVE;
    }
    break;
  }
}
