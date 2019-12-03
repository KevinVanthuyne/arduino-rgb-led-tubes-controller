#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class SingleColorSweepBackAndForth : public Program
{
public:
  SingleColorSweepBackAndForth() : Program(),
                                   currentCycle(0),
                                   currentColor(getRandomNumber(0, (sizeof(colors) / sizeof(colors[0])) - 1)),
                                   previousColor(0),
                                   currentPos(0),
                                   isFadingOut(false),
                                   isGoingUp(true) {}

  int runIteration(uint8_t speed)
  {
    fadeSteps = map(speed, 0, 255, 8, 0);
    cyclesToChangeColor = map(speed, 0, 255, 4, 20);

    // reset everything after a full sweep, according to the current direction
    if (isGoingUp && currentPos == pixelsPerTube)
    {
      // if the completed sweep was fading out, invert the startPos
      if (isFadingOut)
        currentPos = pixelsPerTube - 1;
      // if it was coloring, start from the same startPos again to fade out in the same direction
      else
        currentPos = 0;
      reset();
    }
    else if (!isGoingUp && currentPos == 0)
    {
      if (isFadingOut)
        currentPos = 0;
      else
        currentPos = pixelsPerTube - 1;
      reset();
    }

    if (!isFadingOut)
    {
      for (CRGB *ledStrip : ledStrips)
      {
        if (fadeSteps > 1)
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
    {
      if (isGoingUp)
        currentPos++;
      else
        currentPos--;
    }

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
  bool isGoingUp;

  // reset all params
  void reset()
  {
    currentIteration = 0;
    if (isFadingOut && currentCycle % cyclesToChangeColor == 0)
    {
      previousColor = currentColor;
      currentColor = getRandomNumber(0, 8, previousColor);
      currentCycle = 0;
    }
    currentCycle++;
    if (isFadingOut)
    {
      FastLED.clear(); // to get rid of the last few pixels if any remain
      isGoingUp = !isGoingUp;
    }
    isFadingOut = !isFadingOut;
  }
};