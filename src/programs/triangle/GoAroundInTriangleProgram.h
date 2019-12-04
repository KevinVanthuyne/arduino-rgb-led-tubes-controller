#pragma once

#include "../../Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class GoAroundInTriangleProgram : public Program
{
public:
  GoAroundInTriangleProgram() : Program(),
                                currentPos(0),
                                currentColor(random(0, amountOfColors())),
                                previousColor(0),
                                currentStrip(0),
                                currentCycle(0) {}

  int runIteration(uint8_t speed)
  {
    int fadeOutSpeed = map(speed, 0, 255, 1, 12);
    int fadeInSteps = map(speed, 0, 255, 4, 0);

    for (CRGB *ledStrip : ledStrips)
    {
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeOutSpeed);
    }

    // next strip if the end was reached
    if (currentPos >= pixelsPerTube)
    {
      currentStrip++;
      currentPos = 0;

      if (currentStrip >= 3)
      {
        currentStrip = 0;
        currentCycle++;
      }
    }

    if (currentCycle == 4)
    {
      currentColor = getRandomNumber(0, amountOfColors(), currentColor);
      currentCycle = 0;
    }

    CRGB fadedColor = colors[currentColor];
    if (fadeInSteps > 0)
      fadedColor /= fadeInSteps;
    ledStrips[currentStrip][currentPos] += fadedColor;     // left triangle
    ledStrips[currentStrip + 3][currentPos] += fadedColor; // right triangle

    FastLED.show();

    currentIteration++;
    if (fadeInSteps == 0 || currentIteration % fadeInSteps == 0)
      currentPos++;

    return 1;
  }

private:
  uint8_t hue;
  int currentPos;
  int currentColor;
  int previousColor;
  int currentStrip;
  int currentCycle;
};