#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class AlternatingHalvesProgram : public Program
{
public:
  AlternatingHalvesProgram() : Program(),
                               isFirstHalfOn(true),
                               currentColor(getRandomNumber(0, amountOfColors())) {}

  int runIteration(uint8_t speed)
  {
    int newColorSpeed = map(speed, 0, 255, 8, 60);
    FastLED.clear();

    for (CRGB *ledStrip : ledStrips)
    {
      if (isFirstHalfOn)
        for (int i = 0; i < floor(pixelsPerTube / 2); i++)
          ledStrip[i] = colors[currentColor];
      else
        for (int i = floor(pixelsPerTube / 2); i < pixelsPerTube; i++)
          ledStrip[i] = colors[currentColor];
    }

    FastLED.show();

    isFirstHalfOn = !isFirstHalfOn;
    currentIteration++;
    if (currentIteration % newColorSpeed == 0)
      currentColor = getRandomNumber(0, amountOfColors(), currentColor);

    return map(speed, 0, 255, 1000, 50);
  }

private:
  bool isFirstHalfOn;
  int currentColor;
};