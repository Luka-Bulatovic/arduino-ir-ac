// DisplayController.cpp
#include "DisplayController.h"

DisplayController::DisplayController() {
  display = new Adafruit_SSD1306(screenWidth, screenHeight, &Wire, -1);
}

void DisplayController::initialize() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
}

void DisplayController::show(const char* message) {
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(WHITE);
  display->setCursor(0, 0);
  display->println(message);
  display->display();
}