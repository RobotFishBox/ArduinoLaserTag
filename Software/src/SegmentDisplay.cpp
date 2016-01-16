/*
 Segment Display.
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
   Created to control 2, 3, and 4 digit displays.

 */

#include "SegmentDisplay.h"
#include "arduino.h"

SegmentDisplay::SegmentDisplay (int pinSegments[], int pinPower[], int digits){
  _maxDigits = digits;
  
  _pinSegments = &pinSegments[0];
  _pinPower = &pinPower[0];
  
  _digitCounter = 0;
  _isEnabled = true;
 
  int i;
  for (i = 0; i < _maxDigits; i++){
    setNullDigit (i);
    setDot (false, i);
    pinMode (_pinPower[i], OUTPUT);
    digitalWrite (_pinPower[i], LOW);
  }
  for (i = 0; i < 8; i++){
    pinMode (_pinSegments[i], OUTPUT);
    digitalWrite (_pinSegments[i], HIGH);
  } 
  
}

void SegmentDisplay::updateDisplay (){
  if (_isEnabled){
    digitalWrite (_pinPower[_digitCounter], LOW);                             //Turn current digit off
    if (++_digitCounter >= 4){                                                //reset counter if overflow
      _digitCounter = 0;
    }
    
    byte mask = 1;
    byte data = pgm_read_byte(segmentDisplayNumbers_PGM + _digits[_digitCounter]);
    for (int i = 0; i < 8; i++){      //assign all new segments
        digitalWrite (_pinSegments[i], (data & mask));
        mask <<= 1;
    }
    digitalWrite (_pinSegments[7], _dots[_digitCounter]);
    digitalWrite (_pinPower[_digitCounter], HIGH);                              //Turn next digit on
  }
}

void SegmentDisplay::setDigits (int number, int startDigit, int digits){
  while (number > 0 && startDigit >= 0 && digits > 0) {  //separate the numbers
     _digits[startDigit] = number % 10;
     number /= 10;
     startDigit--;
     digits--;
  }
  while (digits > 0 && startDigit >= 0){        //fill the rest with zeros
     _digits[startDigit] = 0;
     startDigit--;
     digits--;
  }
}

void SegmentDisplay::setDot(boolean isEnabled, int digit){
  if (isEnabled){
    _dots[digit] = LOW;
  }else{
    _dots[digit] = HIGH;
  }
}

void SegmentDisplay::setNullDigit (int digit){
   _digits[digit] = 10;
}

void SegmentDisplay::setEnabled (boolean isEnabled){
  if (isEnabled){
    digitalWrite (_pinPower[_digitCounter], HIGH);   //Turn digit on
    _isEnabled = true;
  }else{
    digitalWrite (_pinPower[_digitCounter], LOW);   //Turn digit off
    _isEnabled = false;
  }
}

void SegmentDisplay::setLetters (int letters[], int digits){
  for (int i = 0; i < digits; i++){
    _digits[i] = letters[i];
  }
}
