/*
    gamepad.ino is a HID keyboard demonstration code for the Bluno-Bee
    (BLE-Link) and DFRobot Wireless Gamepad v2
    
    Copyright (C) 2017 C.Y. Tan Contact:
    cytan299@yahoo.com

    This file is part of gamepad

    gamepad.ino is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    gamepad.ino is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gamepad.ino.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "BLEHID.h"
#include "EEPROM.h"
#include "DFBLE.h"

#define BLUETOOTH_SERIAL_RATE 115200
#define shackMotorPin 2

DFBLEClass gamepad;


int buttonState[17];
int initButtonState[17];
String buttonNames[] = {
  "J2","J1","","S2","S1","UP","LEFT","DOWN","RIGHT","1","4","2","3","RZ1","RZ2","LZ1","LZ2"};
uint8_t buttonValue[]={
  HID_KEYBOARD_T, // J2
  HID_KEYBOARD_Y, // J1
  0,
  HID_KEYBOARD_G, // S2
  HID_KEYBOARD_H, // S1
  HID_KEYBOARD_E, // UP
  HID_KEYBOARD_S, // LEFT
  HID_KEYBOARD_X, // DOWN
  HID_KEYBOARD_D, // RIGHT
  HID_KEYBOARD_1, // 1
  HID_KEYBOARD_4, // 4
  HID_KEYBOARD_2, // 2
  HID_KEYBOARD_3, // 3
  HID_KEYBOARD_6, // RZ1
  HID_KEYBOARD_7, // RZ2
  HID_KEYBOARD_8, // LZ1
  HID_KEYBOARD_9, // LZ2
};


int joystick[4];
int AnalogButton[2];

void InitIO(){ 
  for(int i = 0; i < 17; i++) 
  pinMode(i, INPUT); 
  pinMode(shackMotorPin,OUTPUT);
  digitalWrite(shackMotorPin,LOW);  // Stop shacking of the gamepad 
}

void DataUpdate(){
  
  for(int i = 3; i < 17; i++)  buttonState[i] = digitalRead(i);
  buttonState[0] = analogRead(0);
  buttonState[1] = analogRead(1);
  for(int i = 0; i < 4; i++)  joystick[i] = analogRead(i);
  for(int i = 4; i < 6; i++)  AnalogButton[i-4] = analogRead(i);
  
}

void SendData()
{
  for(int i=3; i<17; i++){
    if(buttonState[i] != initButtonState[i]){
  
      gamepad.press_key(buttonValue[i]);
      delay(5);
      gamepad.press_key(0); 
    }  
  }

  // for the joystick fire buttons
  for(int i=0; i<2; i++){
    if(buttonState[i] < 512){
      gamepad.press_key(buttonValue[i]);
      delay(5);
      gamepad.press_key(0);
    }
  }

  // for the left joystick up/down
  if(AnalogButton[0] < 10){
    gamepad.press_key(HID_KEYBOARD_DOWN_ARROW);
    delay(5);
    gamepad.press_key(0);
  }
  else {
    if(AnalogButton[0] > 1000){
     gamepad.press_key(HID_KEYBOARD_UP_ARROW);
     delay(5);
     gamepad.press_key(0);  
    }    
  }

  // for left joystick left/right
 if(AnalogButton[1] < 10){
    gamepad.press_key(HID_KEYBOARD_RIGHT_ARROW);
    delay(5);
    gamepad.press_key(0);
  }
  else {
    if(AnalogButton[1] > 1000){
     gamepad.press_key(HID_KEYBOARD_LEFT_ARROW);
     delay(5);
     gamepad.press_key(0);  
    }    
  }


// for the right joystick up/down
  if(joystick[2] < 10){
    gamepad.press_key(HID_KEYBOARD_M);
    delay(5);
    gamepad.press_key(0);
  }
  else {
    if(joystick[2] > 1000){
     gamepad.press_key(HID_KEYBOARD_I);
     delay(5);
     gamepad.press_key(0);  
    }    
  }

  // for right joystick left/right
 if(joystick[3] < 10){
    gamepad.press_key(HID_KEYBOARD_K);
    delay(5);
    gamepad.press_key(0);
  }
  else {
    if(joystick[3] > 1000){
     gamepad.press_key(HID_KEYBOARD_J);
     delay(5);
     gamepad.press_key(0);  
    }    
  }

  

}


void setup() {
  // initialize the BLUETOOTH and SERIAL port
  Serial1.begin(BLUETOOTH_SERIAL_RATE);
  Serial.begin(115200);

  for(int i = 3; i < 17; i++)  initButtonState[i] = digitalRead(i);
  initButtonState[0] = analogRead(0);
  initButtonState[1] = analogRead(1);
}

void loop() {
#ifdef AAAAAAAAAAAAAA
    if(Serial.available()){
      char input = Serial.read();
      gamepad.press_key(HID_KEYBOARD_A);
      delay(10);
      gamepad.press_key(0);  
    }
#endif
  static unsigned long timer = 0;

  if(millis() - timer > 200){  // manage the updating freq of all the controlling information
    DataUpdate();  //read the buttons and the joysticks data
//  printData();   //print the datas and states
    SendData();
    timer = millis(); 
  }

    
 

}
