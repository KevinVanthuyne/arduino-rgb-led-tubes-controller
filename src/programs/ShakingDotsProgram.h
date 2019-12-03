#pragma once

#include "Program.h"
#include "../Utils.h"

class ShakingDotsProgram : public Program
{
public:
  ShakingDotsProgram() : Program(),
                         palette(PartyColors_p) {}

  int runIteration(uint8_t speed)
  {
    uint8_t bpm = map(speed, 0, 255, 30, 128);
    uint8_t beat = beatsin8(bpm, 64, 255);

    for (CRGB *ledStrip : ledStrips)
      for (int i = 0; i < pixelsPerTube; i++)
        ledStrip[i] = ColorFromPalette(palette, currentIteration + (i * 2), beat - currentIteration + (i * 10));

    FastLED.show();
    currentIteration++;

    return 1;
  }

private:
  CRGBPalette16 palette;
};