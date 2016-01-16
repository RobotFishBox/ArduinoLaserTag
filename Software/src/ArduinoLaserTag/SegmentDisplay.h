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
   Segment display pattern:
   _       1
  |_|    0 3 2        
  |_|.   4 5 6 7
  
  For a four digit display:
  
  _ _ _ _   0 1 2 3

 */

#ifndef SegmentDisplay_h
#define SegmentDisply_h

#include "Configuration.h"
#include "arduino.h"

const byte PROGMEM segmentDisplayNumbers_PGM[] = {
  B0001000,          //0, O
  B0111011,          //1, I
  B1000001,          //2
  B0010001,          //3
  B110010,           //4
  B0010100,          //5 
  B0000100,          //6
  B0111000,          //7
  B0000000,          //8, B
  B0010000,          //9
  B1111111,          //null represented by 10
  B0100000,          //A
  B1001100,          //C
  B1000100,          //E
  B0011100,          //F
  B0001100,          //G
  B0100010,          //H
  B0001110,          //J
  B1001110,          //L
  B0101000,          //n
  B1100000,          //P
  B0010100,          //S
  B0001010,          //U
};

class SegmentDisplay
{
public:
  SegmentDisplay (int pinSegments[], int pinPower[], int digits);
  void updateDisplay ();                                         //Turn off current digit. Light up the next digit
  void setDigits (int number, int startDigit, int digits);       //Sets a number to the display
  void setDot (boolean isEnabled, int digit);                    //Sets the dot on the display
  void setNullDigit (int digit);                                 //Blanks out a digit
  void setEnabled (boolean isEnabled);                           //Stops the display
  void setLetters (int letters[], int digits);                                     //Stops the display
  
private:
  int _digits[MAX_SEGMENT_DISPLAY_DIGITS];
  boolean _dots[MAX_SEGMENT_DISPLAY_DIGITS];
  
  int _digitCounter;
  int _maxDigits;
  boolean _isEnabled;

  int *_pinSegments;
  int *_pinPower;
};

#endif
