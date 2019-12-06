#pragma once

#include "Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class LeftRightTriangleProgram : public Program
{
public:
  LeftRightTriangleProgram() : Program(),
                               isLeftOn(true) {}

  int runIteration(uint8_t speed)
  {
    int lightUpInterval = map(speed, 0, 255, 160, 32);
    int fadeSpeed = map(speed, 0, 255, 1, 12);

    for (CRGB *ledStrip : ledStrips)
    {
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);
    }

    if (currentIteration % lightUpInterval == 0)
    {
      if (isLeftOn)
      {
        fill_solid(ledStrips[3], pixelsPerTube, CRGB::White);
        fill_solid(ledStrips[4], pixelsPerTube, CRGB::White);
        fill_solid(ledStrips[5], pixelsPerTube, CRGB::White);
      }
      else
      {
        fill_solid(ledStrips[0], pixelsPerTube, CRGB::White);
        fill_solid(ledStrips[1], pixelsPerTube, CRGB::White);
        fill_solid(ledStrips[2], pixelsPerTube, CRGB::White);
      }
      isLeftOn = !isLeftOn;
    }

    FastLED.show();

    currentIteration++;

    return 1;
  }

private:
  bool isLeftOn;
};