/*
 Auxilary controls for triggger, reload, LEDs and motor.
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
 
#ifndef Auxilary_h
#define Auxilary_h

#include "arduino.h"

class Auxilary
{
public:
  Auxilary (byte pinMotor, byte pinTrigger, byte pinReload, byte pinLEDs);
  void turnMotorOn(boolean cmd);
  void turnLedOn(boolean cmd);
  void refreshCounts();
  void updateAux();
  int triggerValue();
  int reloadValue();
  boolean triggered(int threshold, int debounce);
  boolean reload(int threshold, int debounce);
private:
  byte _pinMotor;
  byte _pinTrigger;
  byte _pinReload;
  byte _pinLEDs;
  
  int _triggerCount;
  int _reloadCount;
};

#endif
