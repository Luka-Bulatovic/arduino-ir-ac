// DisplayController.h
#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class DisplayController {
  private:
    const int screenWidth = 128;
    const int screenHeight = 64;
    Adafruit_SSD1306* display;

  public:
    DisplayController();

    void initialize();
    void show(const char* message);
};

#endif
