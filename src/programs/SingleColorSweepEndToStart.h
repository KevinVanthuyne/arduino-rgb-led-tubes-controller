#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class SingleColorSweepEndToStart : public Program
{
public:
  SingleColorSweepEndToStart() : Program(),
                                 currentCycle(0),
                                 currentColor(0),
                                 previousColor(0),
                                 currentPos(pixelsPerTube - 1),
                                 isFadingOut(true) {}

  int runIteration(uint8_t speed)
  {
    fadeSteps = map(speed, 0, 255, 8, 0);
    cyclesToChangeColor = map(speed, 0, 255, 4, 20);

    // reset everything after a full sweep
    if (currentPos == 0)
    {
      currentIteration = 0;
      currentPos = pixelsPerTube - 1;
      if (isFadingOut && currentCycle % cyclesToChangeColor == 0)
      {
        previousColor = currentColor;
        currentColor = getRandomNumber(0, 8, previousColor);
        currentCycle = 0;
      }
      currentCycle++;
      if (isFadingOut)
        FastLED.clear(); // to get rid of the last few pixels if any remain
      isFadingOut = !isFadingOut;
    }

    if (!isFadingOut)
    {
      for (CRGB *ledStrip : ledStrips)
      {
        if (fadeSteps > 0)
        {
          CRGB fadedColor = colors[currentColor];
          fadedColor /= fadeSteps;
          ledStrip[currentPos] += fadedColor;
        }
        else
          ledStrip[currentPos] = colors[currentColor];
      }
    }
    else
    {
      for (CRGB *ledStrip : ledStrips)
      {
        if (fadeSteps > 1)
        {
          CRGB fadedColor = colors[currentColor];
          fadedColor /= fadeSteps;
          ledStrip[currentPos] -= fadedColor;
        }
        else
          ledStrip[currentPos] = CRGB::Black;
      }
    }

    currentIteration++;
    if (fadeSteps == 0 || currentIteration % fadeSteps == 0)
      currentPos--;

    FastLED.show();

    return 0;
  }

private:
  uint8_t currentCycle;
  uint8_t cyclesToChangeColor;
  int fadeSteps;
  int currentColor;
  int previousColor;
  int currentPos;
  bool isFadingOut;
};