#pragma once

#include "../../Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class RippleProgram : public Program
{
public:
  RippleProgram() : Program(),
                    currentColor(random(0, amountOfColors())),
                    currentValue(128),
                    previousColor(0),
                    currentCycle(0) {}

  int runIteration(uint8_t speed)
  {
    int fadeInSteps = map(speed, 0, 255, 1, 0);

    if (currentValue > 255)
    {
      currentValue = 128; // start at 128 to only use ease out of sine wave (not ease in)
      currentCycle++;
      if (currentCycle == 8)
      {
        currentColor = getRandomNumber(0, amountOfColors(), currentColor);
        currentCycle = 0;
      }
    }

    int easeOutVal = ease8InOutQuad(currentValue);             // convert the linear 0-255 to ease out values
    int mappedValue = map(easeOutVal, 128, 255, 0, 255);       // stretch the easeOut value to the full 0-255 range
    int lerpVal = lerp8by8(0, pixelsPerTube - 1, mappedValue); // map it to the number of LED's

    CRGB fadedColor = colors[currentColor];
    if (fadeInSteps > 0)
      fadedColor /= fadeInSteps;

    ledStrips[0][lerpVal] += fadedColor;
    ledStrips[3][lerpVal] += fadedColor;
    ledStrips[2][pixelsPerTube - 1 - lerpVal] += fadedColor;
    ledStrips[5][pixelsPerTube - 1 - lerpVal] += fadedColor;

    for (CRGB *ledStrip : ledStrips)
      fadeToBlackBy(ledStrip, pixelsPerTube, 16);

    FastLED.show();

    if (fadeInSteps == 0 || currentIteration % fadeInSteps == 0)
      currentValue++;
    currentIteration++;

    return 1;
  }

private:
  int currentColor;
  int currentValue;
  int previousColor;
  int currentCycle;
};