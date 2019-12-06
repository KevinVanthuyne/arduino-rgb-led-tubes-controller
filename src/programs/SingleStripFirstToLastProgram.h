#pragma once

#include "Program.h"
#include "../Utils.h"

class SingleStripFirstToLastProgram : public Program
{
public:
  SingleStripFirstToLastProgram() : Program(),
                                    currentStrip(1),
                                    currentColor(getRandomNumber(0, amountOfColors())) {}

  int runIteration(uint8_t speed)
  {
    FastLED.clear();
    fill_solid(ledStrips[currentStrip - 1], pixelsPerTube, colors[currentColor]);
    FastLED.show();

    if (currentStrip < (sizeof(ledStrips) / sizeof(ledStrips[0])))
      currentStrip++;
    else
    {
      currentStrip = 1;
      previousColor = currentColor;
      currentColor = getRandomNumber(0, 8, previousColor);
    }

    return map(speed, 0, 255, 1000, 50);
  }

private:
  unsigned int currentStrip;
  int currentColor;
  int previousColor;
};