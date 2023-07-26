// DisplayController.cpp
#include "DisplayController.h"

DisplayController::DisplayController() {}

void DisplayController::initialize() {
  display.begin(&Adafruit128x64, 0x3C, -1);
}

void DisplayController::show(const char* message) {
  display.setFont(Adafruit5x7);

  display.clear();
  display.println(message);
  //oled.set2X();
  //oled.set1X();
}