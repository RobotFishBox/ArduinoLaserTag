/*
 Game player controls
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

#ifndef Player_h
#define Player_h

#include "arduino.h"
#include "SoundLibrary.h"
#include "Configuration.h"

class Player
{
public:
  Player ();
  
  int getState();
  int getHealth();
  
  byte *getSound ();
  
  boolean playSound ();
  
  void setIsHit (boolean value);
  void setIRCode (unsigned long value);
  void setSoundPlaying (int value);
  
  void updatePlayer ();
  
private:
  byte *_currAction;
  byte *_currSound;
  
  int _health;
  int _irCode;
  
  byte _state;
  
  boolean _playSound;
  boolean _isHit;
  boolean _soundPlaying;      //used for waiting for sound to finish.
  
  void resetInputFlags ();
  void resetOutputFlags ();
  void runAction (byte value);
};

#endif
