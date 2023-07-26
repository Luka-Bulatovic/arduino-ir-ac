// DisplayController.h
#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>

class DisplayController {
private:
  const static int SCREEN_WIDTH = 128;
  const static int SCREEN_HEIGHT = 64;
  SSD1306AsciiAvrI2c display;

public:
  DisplayController();

  void initialize();
  void show(const char* message);
};

#endif
