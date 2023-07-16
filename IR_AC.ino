#include "DisplayController.h"
#include "SerialCommunication.h"

DisplayController* display;
SerialCommunication* communication;

const String debugTag = "e";
String loopMsg = "Looping...";

void handleDisplayMessage(const char* message) {
  Serial.println(message);
  display->show(message);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  display = new DisplayController();
  display->initialize();
  // delay(500);
  // display->show("Hello, World!");

  // Setup Serial Communication between ATMega and ESP8266
  communication = new SerialCommunication(&Serial);

  // Income message handlers
  communication->registerHandler("display", handleDisplayMessage);
}
// 
void loop() {
  // communication->sendMessage(debugTag, loopMsg);
  communication->handleMessage();

  // delay(500);
}
