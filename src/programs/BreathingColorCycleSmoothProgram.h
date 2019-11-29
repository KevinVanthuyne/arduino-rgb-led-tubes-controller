#pragma once

#include "Program.h"
#include "../Utils.h"

class BreathingColorCycleSmoothProgram : public Program
{
public:
  BreathingColorCycleSmoothProgram() : Program(), hue(0) {}
  int runIteration(uint8_t speed)
  {
    if (currentIteration <= 255)
      brightness = currentIteration;
    else if (currentIteration <= 446)
      brightness = 510 - currentIteration;
    else
      currentIteration = 64;

    if (currentIteration % 64 == 0)
      hue++;

    for (CRGB *ledStrip : ledStrips)
    {
      fill_solid(ledStrip, pixelsPerTube, CHSV(hue, 255, brightness));
    }
    FastLED.show();

    // bigger steps for faster speed or smaller steps for slower speed
    int delayRange = 32;
    int currentDelay = map(speed, 0, 255, delayRange, 1);

    if (currentDelay < (delayRange * 0.25))
      currentIteration += 6;
    else if (currentDelay < (delayRange * 0.5))
      currentIteration += 4;
    else
      currentIteration += 2;

    Serial.println(brightness);

    return currentDelay;
  }

private:
  uint8_t hue;
  uint8_t brightness;
};