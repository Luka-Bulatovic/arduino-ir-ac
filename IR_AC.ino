#include "DisplayController.h"
#include "SerialCommunication.h"
#include "MideaACController.h"
#include <MemoryFree.h>

DisplayController display;
SerialCommunication communication;
MideaACController acController;
char displayKey[] = "display";
char acKey[] = "ac";

void handleDisplayMessage(const char* message) {
  display.show(message);
}

void handleACMessage(const char* command) {
  /*
    Command format:
      off or xxyz
    where:
      xx = temperature (celsius)
      y = mode : 0 - auto; 1 - cool; 2 - dry; 3 - heat
      z = fan speed : 0 - off; 1 - low; 2 - medium; 3 - high; 4 - auto
  */

  if(strcmp(command, "off") == 0) {
    acController.stop();
    return;
  }

  int commandVal = atoi(command);
  
  // Wrong format
  if(commandVal < 1000 || strlen(command) != 4) {
    display.show("AC: Wrong format");
    return;
  }
  
  int temperature = commandVal / 100;
  int mode = (commandVal / 10) % 10;
  int fanSpeed = commandVal % 10;

  if(temperature < 17 || temperature > 30) {
    display.show("AC: Wrong temperature");
    return;
  }

  if(mode < 0 || mode > 3) {
    display.show("AC: Wrong mode");
    return;
  }

  if(fanSpeed < 0 || fanSpeed > 4) {
    display.show("AC: Wrong fan speed");
    return;
  }

  // Convert to correct AcMode
  enum AcMode acMode;
  switch(mode) {
    case 0:
      acMode = AcMode::AUTO;
      break;
    case 1:
      acMode = AcMode::COOL;
      break;
    case 2:
      acMode = AcMode::HUMIDITY_EXTRACTION;
      break;
    case 3:
      acMode = AcMode::HEAT;
      break;
    default:
      break;
  }

  // Convert to correct FanSpeed
  enum FanSpeed acFanSpeed;
  switch(fanSpeed) {
    case 0:
      acFanSpeed = FanSpeed::OFF;
      break;
    case 1:
      acFanSpeed = FanSpeed::SPEED_1;
      break;
    case 2:
      acFanSpeed = FanSpeed::SPEED_2;
      break;
    case 3:
      acFanSpeed = FanSpeed::SPEED_3;
      break;
    case 4:
      acFanSpeed = FanSpeed::AUTO;
      break;
    default:
      break;
  }

  // Execute command
  acController.executeCommand(acMode, temperature, acFanSpeed);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB
  }

  pinMode(3, OUTPUT);

  display.initialize();

  // Setup Serial Communication between ATMega and ESP8266
  communication.setStream(&Serial);

  acController.irsend.begin(3);
  // Initialize MideaACController

  // Income message handlers
  communication.registerHandler(displayKey, handleDisplayMessage);
  communication.registerHandler(acKey, handleACMessage);
}

void loop() {
  communication.handleMessage();
}
