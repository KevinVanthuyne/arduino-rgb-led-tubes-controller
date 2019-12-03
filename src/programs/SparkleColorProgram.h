#pragma once

#include "Program.h"
#include "../Utils.h"

class SparkleColorProgram : public Program
{
public:
  SparkleColorProgram() : Program(), hue(getRandomNumber(0, 255)) {}
  int runIteration(uint8_t speed)
  {
    for (CRGB *ledStrip : ledStrips)
    {
      if (currentIteration % 64 == 0)
        hue++;

      int fadeSpeed = map(speed, 0, 255, 2, 10);
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);

      int newSparkleSpeed = map(speed, 0, 255, 16, 2);
      if (currentIteration % newSparkleSpeed == 0)
      {
        int pos = random16(pixelsPerTube);
        for (int i = 0; i < 7; i++)
          if (pos + i < pixelsPerTube)
            ledStrip[pos + i] += CHSV(hue, 255, 255);
      }
    }
    FastLED.show();
    currentIteration++;

    return 1;
  }

private:
  uint8_t hue;
};