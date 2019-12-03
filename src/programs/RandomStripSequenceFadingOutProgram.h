#pragma once

#include "Program.h"
#include "../Utils.h"

class RandomStripSequenceFadingOutProgram : public Program
{
public:
  RandomStripSequenceFadingOutProgram() : Program(),
                                          previousStrip(-1),
                                          hue(getRandomNumber(0, 255)),
                                          maxStrips(3)
  {
  }

  int runIteration(uint8_t speed)
  {
    int fadeSpeed = map(speed, 0, 255, 1, 4);
    int lightUpSpeed = map(speed, 0, 255, 64, 16);

    for (CRGB *ledStrip : ledStrips)
    {
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);
    }

    if (currentIteration % lightUpSpeed == 0)
    {
      int amountOfStripsToLight = getRandomNumber(1, maxStrips);
      int stripToAvoid; // to avoid lighting the same strip(s) twice

      for (int i = 0; i < amountOfStripsToLight; i++)
      {
        int newStrip = getRandomNumber(1, sizeof(ledStrips) / sizeof(ledStrips[0]), previousStrip);
        fill_solid(ledStrips[newStrip - 1], pixelsPerTube, CHSV(hue, 255, 255));
        stripToAvoid = newStrip;
      }
      previousStrip = stripToAvoid;
      hue++;
    }

    FastLED.show();

    currentIteration++;

    return 1;
  }

private:
  int previousStrip;
  int hue;
  int maxStrips;
};