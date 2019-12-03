#pragma once

#include "../../Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class ColorUpDownProgram : public Program
{
public:
  ColorUpDownProgram() : Program(),
                         currentColor(random(0, (sizeof(colors) / sizeof(colors[0])) - 1)),
                         isFadingOut(false) {}

  int runIteration(uint8_t speed)
  {
    int fadeSteps = map(speed, 0, 255, 8, 1);

    // set to fade out mode when position gets to the end
    if (!isFadingOut && currentPos >= pixelsPerTube)
    {
      currentIteration = 0;
      currentPos = pixelsPerTube - 1;
      isFadingOut = true;
      // FastLED.clear();
    }

    // set to color mode when position gets to the beginning
    if (isFadingOut && currentPos < 0)
    {
      currentPos = 0;
      currentColor = random(0, (sizeof(colors) / sizeof(colors[0])) - 1);
      isFadingOut = false;
    }

    if (!isFadingOut)
    {
      for (int strip = 0; strip < 6; strip++)
      {
        CRGB fadedColor = colors[currentColor];
        fadedColor /= fadeSteps;
        if (strip == 2 || strip == 5)
          ledStrips[strip][currentPos] += fadedColor;
        else if (strip == 1 || strip == 4)
          ledStrips[strip][pixelsPerTube - 1 - currentPos] += fadedColor;
      }
    }
    else
    {
      for (int strip = 0; strip < 6; strip++)
      {
        CRGB fadedColor = CRGB::White;
        fadedColor /= fadeSteps;
        if (strip == 2 || strip == 5)
          ledStrips[strip][currentPos] -= fadedColor;
        else if (strip == 1 || strip == 4)
          ledStrips[strip][pixelsPerTube - 1 - currentPos] -= fadedColor;
      }
    }
    FastLED.show();

    currentIteration++;
    if (currentIteration % fadeSteps == 0)
    {
      if (isFadingOut)
        currentPos--;
      else
        currentPos++;
    }

    return 1;
  }

private:
  uint8_t hue;
  int currentPos;
  int currentColor;
  bool isFadingOut;
};