#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class RainbowProgram : public Program
{
public:
  RainbowProgram() : Program(), hue(getRandomNumber(0, 255)) {}
  int runIteration(uint8_t speed)
  {
    hue++;

    for (CRGB *ledStrip : ledStrips)
    {
      fill_rainbow(ledStrip, pixelsPerTube, hue, 3);
    }
    FastLED.show();

    return map(speed, 0, 255, 50, 1);
  }

private:
  uint8_t hue;
};