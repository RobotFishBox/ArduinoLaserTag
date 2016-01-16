/*
 Arduino Laser Tag firmware.
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
 
#include "SegmentDisplay.h"
#include "Pins.h"
#include "Playtune.h"
#include "IRController.h"
#include "Auxilary.h"
#include "SoundLibrary.h"
#include "Gun.h"

//------------------------------------------------------
// Initialize hardware objects
//------------------------------------------------------

int segmentPinArray[] = SD_SEGMENT_PIN_ARRAY;
int powerPinArray[] = SD_POWER_PIN_ARRAY;
SegmentDisplay gunDisplay(segmentPinArray, powerPinArray, 4);

Playtune speakers;

Auxilary auxComp(MOTOR_PIN, TRIGGER_PIN_ANALOG, RELOAD_PIN_ANALOG, LEDS_PIN);

IRsend irSend;
IRrecv irRecv(IR_RECEIVER_PIN);

decode_results irResults;

//------------------------------------------------------
// Initialize game objects
//------------------------------------------------------

int sdHandGun[] = {SEGMENT_DISPLAY_H , SEGMENT_DISPLAY_G, SEGMENT_DISPLAY_U, SEGMENT_DISPLAY_N};
int sdShotGun[] = {SEGMENT_DISPLAY_S , SEGMENT_DISPLAY_G, SEGMENT_DISPLAY_U, SEGMENT_DISPLAY_N};
int sdBow[] = {SEGMENT_DISPLAY_B , SEGMENT_DISPLAY_O, SEGMENT_DISPLAY_U, SEGMENT_DISPLAY_U};
int sdMachineGun[] = {SEGMENT_DISPLAY_A , SEGMENT_DISPLAY_C, SEGMENT_DISPLAY_H, SEGMENT_DISPLAY_I};

int *sdGunsList[] = {sdHandGun, sdShotGun, sdBow, sdMachineGun};
int menuGunTypes[] ={GT_HANDGUN , GT_SHOTGUN, GT_BOW, GT_MACHINE_GUN};

Gun laserGun;

void setup() { 
  speakers.tune_initchan (SOUND_PIN_1); 
  speakers.tune_initchan (SOUND_PIN_2);
  
  gunSelectionMenu ();
  
  irRecv.enableIRIn();
}

void loop() {
  // update player inputs
  if (irRecv.decode(&irResults)) {
    irRecv.resume(); // Receive the next value
  } else {
    
  }
  
  laserGunUpdate();

  // finish update
  auxComp.turnMotorOn (speakers.tune_motor_running);
  gunDisplay.updateDisplay ();
  
}

void laserGunUpdate() {
  // laser gun inputs
  laserGun.setTrigger (auxComp.triggered(TRIGGER_THRESHOLD, DEBOUNCE_COUNT));
  laserGun.setReload (auxComp.reload(RELOAD_THRESHOLD, DEBOUNCE_COUNT));
  laserGun.setSoundPlaying (speakers.tune_playing);
  

  // lasergun updates 
  laserGun.updateGun ();
 
   // laser gun outputs
  if (laserGun.sendIR ()) {
    gunDisplay.setEnabled (false);
    speakers.tune_disableInterrupts();
    irSend.sendIR (laserGun.getIRCode (), IR_BITS);
    irRecv.enableIRIn();
    gunDisplay.setEnabled (true);
  }
  
  if (laserGun.playSound ()) {
    speakers.tune_playscore (laserGun.getGunSound ());
  }

  if (laserGun.getState () == GUN_STATE_RELOAD) {
    gunDisplay.setDigits (laserGun.getAmmoSupply (), 3, 4);
    gunDisplay.setDot (false, 1);
  } else {
    gunDisplay.setDigits (laserGun.getAmmoClip (), 3, 4);
    gunDisplay.setDot (true, 1);
  }
}

void gunSelectionMenu (){
  speakers.tune_playscore ((byte *)soundSecret_PRG);
  while (speakers.tune_playing){}
  int i = 0;
  gunDisplay.setLetters (sdGunsList[i], 4);
  while (auxComp.reload(TRIGGER_THRESHOLD, DEBOUNCE_COUNT)) {
    if (auxComp.triggered(TRIGGER_THRESHOLD, DEBOUNCE_COUNT)) {
      if (++i >= GT_NUM_GUNS) { i = 0;}
      gunDisplay.setLetters (sdGunsList[i], 4);
      speakers.tune_playscore ((byte *)soundAmmoEmpty_PRG);
      while (auxComp.triggerValue() >= TRIGGER_THRESHOLD){
        gunDisplay.updateDisplay ();
      }
    }
    gunDisplay.updateDisplay ();
  }
  
  switch(menuGunTypes[i]) {
    case GT_BOW:
      laserGun.setGunType (GT_BOW, GT_BOW_INIT_AMOUNT, GT_BOW_RELOAD_AMOUNT);
      break;
    case GT_HANDGUN:
      laserGun.setGunType (GT_HANDGUN, GT_HANDGUN_INIT_AMOUNT, GT_HANDGUN_RELOAD_AMOUNT);
      break;
    case GT_SHOTGUN:
      laserGun.setGunType (GT_SHOTGUN, GT_SHOTGUN_INIT_AMOUNT, GT_SHOTGUN_RELOAD_AMOUNT);
      break;
    case GT_MACHINE_GUN:
      laserGun.setGunType (GT_MACHINE_GUN, GT_MACHINE_GUN_INIT_AMOUNT, GT_MACHINE_GUN_RELOAD_AMOUNT);
      break;
  }
}
