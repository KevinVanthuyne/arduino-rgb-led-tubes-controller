#pragma once

#include "Program.h"
#include "../Utils.h"

class StackerProgram : public Program
{
public:
  StackerProgram() : Program(),
                     hue(0),
                     blockSize(5),
                     uncoloredDistance(pixelsPerTube),
                     currentPos(0) {}

  int runIteration(uint8_t speed)
  {
    fadeSteps = map(speed, 0, 255, 8, 0);

    // clear the strips when running for the first time
    if (currentIteration == 0)
      FastLED.clear();

    if (currentPos == uncoloredDistance)
    {
      // decrease the uncoloredDistance for the next iteration
      if ((uncoloredDistance - blockSize) > 0)
        uncoloredDistance -= blockSize;
      // reset the current block to start at the beginning again
      currentPos = 0;
      // clear the strip but color the leds outside of the uncolored distance
      FastLED.clear();
      for (CRGB *ledStrip : ledStrips)
        for (int i = 0; i < pixelsPerTube - uncoloredDistance; i++)
          ledStrip[uncoloredDistance + i] = CRGB::Red;
    }

    for (CRGB *ledStrip : ledStrips)
    {
      if (fadeSteps > 0)
      {
        ledStrip[currentPos] += CRGB(254 / fadeSteps, 0, 0);
        ledStrip[currentPos - blockSize] -= CRGB(254 / fadeSteps, 0, 0);
      }
      else
      {
        ledStrip[currentPos] = CRGB::Red;
        ledStrip[currentPos - blockSize] = CRGB::Black;
      }
    }

    FastLED.show();

    if (uncoloredDistance < blockSize)
    {
      currentIteration = 0;
      currentPos = 0;
      uncoloredDistance = pixelsPerTube;
    }
    else
    {
      currentIteration++;
      if (fadeSteps == 0 || currentIteration % fadeSteps == 0)
        currentPos++;
    }

    return 0;
  }

private:
  uint8_t hue;
  uint8_t blockSize;
  uint8_t uncoloredDistance; // amount of leds that are not colored yet
  int currentPos;
  int fadeSteps; // in how many iterations does the current pixel fade in
};