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
 
 #include "Auxilary.h"
 
Auxilary::Auxilary (byte pinMotor, byte pinTrigger, byte pinReload, byte pinLEDs){
   _pinMotor = pinMotor;
   pinMode(_pinMotor, OUTPUT);
   turnMotorOn(false);
   
   _pinLEDs = pinLEDs;
   pinMode(_pinLEDs, OUTPUT);
   turnLedOn(false);
   
   _pinTrigger = pinTrigger;
   _pinReload = pinReload;
   
   refreshCounts();
}
 
void Auxilary::turnMotorOn(boolean cmd){
   digitalWrite(_pinMotor, cmd);
}
 
void Auxilary::turnLedOn(boolean cmd){
   digitalWrite(_pinLEDs, cmd);
}
 
int Auxilary::triggerValue(){
   return (analogRead(_pinTrigger));
}
 
int Auxilary::reloadValue(){
   return (analogRead(_pinReload));
}

void Auxilary::refreshCounts() {
   _triggerCount = 0;
   _reloadCount = 0;
}
 
boolean Auxilary::triggered(int threshold, int debounce) {
   if (analogRead(_pinTrigger) > threshold) { // debounce check
     if (_triggerCount < debounce) {
       _triggerCount ++;
       return false;
     } else {
       return true;
     }
   } else {
     _triggerCount = 0;
     return false;
   }
}
  
boolean Auxilary::reload(int threshold, int debounce) {
   if (analogRead(_pinReload) > threshold) { // debounce check
     if (_reloadCount < debounce) {
       _reloadCount ++;
       return false;
     } else {
       return true;
     }
   } else {
     _reloadCount = 0;
     return false;
   }
}
