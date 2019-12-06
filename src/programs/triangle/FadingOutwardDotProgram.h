#pragma once

#include "../../Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class FadingOutwardDotProgram : public Program
{
public:
  FadingOutwardDotProgram() : Program(),
                              hue(random8()) {}

  int runIteration(uint8_t speed)
  {
    int moveInterval = map(speed, 0, 255, 4, 0);
    int fadeSpeed = map(speed, 0, 255, 3, 15);
    int hueStep = map(speed, 0, 255, 8, 1);

    for (CRGB *ledStrip : ledStrips)
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);

    if (currentIteration >= pixelsPerTube * moveInterval)
    {
      for (int i = 1; i < 10; i++)
      {
        ledStrips[0][i] = CHSV(hue, 255, 255);
        ledStrips[3][i] = CHSV(hue, 255, 255);
        ledStrips[2][pixelsPerTube - 1 - i] = CHSV(hue, 255, 255);
        ledStrips[5][pixelsPerTube - 1 - i] = CHSV(hue, 255, 255);
      }
      hue += hueStep;
      currentIteration = 0;
    }

    if (moveInterval == 0 || currentIteration % moveInterval == 0)
    {
      // move everything over by one led
      for (int i = pixelsPerTube - 1; i > 0; i--)
      {
        ledStrips[0][i] = ledStrips[0][i - 1];
        ledStrips[3][i] = ledStrips[3][i - 1];
      }
      for (int i = 0; i < pixelsPerTube - 1; i++)
      {
        ledStrips[2][i] = ledStrips[2][i + 1];
        ledStrips[5][i] = ledStrips[5][i + 1];
      }
    }

    FastLED.show();

    currentIteration++;

    return 1;
  }

private:
  uint8_t hue;
};