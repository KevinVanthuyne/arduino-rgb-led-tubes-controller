#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class FadingScanlineProgram : public Program
{
public:
  FadingScanlineProgram() : Program(), hue(getRandomNumber(0, 255)) {}
  int runIteration(uint8_t speed)
  {
    if (currentIteration % 32 == 0)
      hue++;
    int bpm = map(speed, 0, 255, 13, 50);

    for (CRGB *ledStrip : ledStrips)
    {
      fadeToBlackBy(ledStrip, pixelsPerTube, 20);
      int pos = beatsin16(bpm, 0, pixelsPerTube - 1);
      ledStrip[pos] += CHSV(hue, 255, 255);
    }
    FastLED.show();
    currentIteration++;

    return 1;
  }

private:
  uint8_t hue;
};