#pragma once

#include "Program.h"
#include "../Utils.h"

class RandomStripSequenceProgram : public Program
{
public:
  RandomStripSequenceProgram() : Program(),
                                 previousStrip(-1),
                                 hue(0),
                                 maxStrips(3)
  {
  }

  int runIteration(uint8_t speed)
  {
    FastLED.clear();
    int amountOfStripsToLight = getRandomNumber(1, maxStrips);
    int stripToAvoid; // to avoid lighting the same strip(s) twice

    for (int i = 0; i < amountOfStripsToLight; i++)
    {
      int newStrip = getRandomNumber(1, sizeof(ledStrips) / sizeof(ledStrips[0]), previousStrip);
      fill_solid(ledStrips[newStrip - 1], pixelsPerTube, CHSV(hue, 255, 255));
      stripToAvoid = newStrip;
    }
    previousStrip = stripToAvoid;

    FastLED.show();

    currentIteration++;
    hue++;

    return map(speed, 0, 255, 1000, 50);
  }

private:
  int previousStrip;
  int hue;
  int maxStrips;
};