#include <Arduino.h>
#include <map>

#include "SPIFFS.h"

#include "BleKeyboard.h"

#include "file.h"
#include "Key.h"
#include "Command.h"
#include "MapKeyboardKey.h"


BleKeyboard bleKeyboard;



void setup() {
  Serial.begin(9600);
  // filesystem file
  SPIFFS.begin();
  
  // init ble 
  Serial.println("Starting BLE work!");
  bleKeyboard.setBatteryLevel(100);
  bleKeyboard.set_version(5);
  bleKeyboard.setName("MacroKeyV3");
  bleKeyboard.begin();

  Serial.println();
  // init command
  String tempFileCommand = readFile(SPIFFS, "/command.csv");
  initCommand(tempFileCommand.c_str());

  // init key
  initKey(tempKey);

  Serial.println();
  for(int i=0; i<maxArraySize; i++){
    if(tempKey[i].gpo != 0) Serial.println(tempKey[i].name);
  }

  // set pinmode on keyGpo
  for(int i=0; i<maxArraySize; i++){
    if (tempKey[i].gpo > 0){
      pinMode(tempKey[i].gpo, INPUT_PULLUP);
    }
  }
}

// function for send keycode on device
void pressButton(String tempKeyString){
    for(int i=0;i<5;i++){
      if(CommandKey[tempKeyString].cmd[i].length() > 0)
        if (MapMediaKeyboardKey[CommandKey[tempKeyString].cmd[i]].key[0]){
          Serial.println(MapMediaKeyboardKey[CommandKey[tempKeyString].cmd[i]].key[0]);
          bleKeyboard.press(MapMediaKeyboardKey[CommandKey[tempKeyString].cmd[i]].key);
        }else{
          bleKeyboard.press(MapKeyboardKey[CommandKey[tempKeyString].cmd[i]]);
        }
    }
    delay(50);
    bleKeyboard.releaseAll();
    delay(200);
    return;
}

// main loop
void loop() {
  if(bleKeyboard.isConnected()) {
    // get button how pressed
    String tempKeyString = getButton();
    if (tempKeyString.length() > 0 && CommandKey[tempKeyString].cmd[0].length() > 0){
      Serial.println(tempKeyString);
      // press button
      pressButton(tempKeyString);
      bleKeyboard.releaseAll();
    }

  }else{
  Serial.println("Waiting 5 seconds...");
  delay(5000);
  }
  // put your main code here, to run repeatedly:
}

