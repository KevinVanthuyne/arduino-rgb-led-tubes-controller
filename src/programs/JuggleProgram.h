#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class JuggleProgram : public Program
{
public:
  JuggleProgram() : Program(),
                    currentPalette(CRGBPalette16(CRGB::Black)),
                    targetPalette(RainbowColors_p),
                    dots(3),
                    resetHue(random8()) {}

  int runIteration(uint8_t speed)
  {
    int beatWaveSpeed = map(speed, 0, 255, 5, 20);
    int fadeSpeed = map(speed, 0, 255, 30, 40);

    if (currentIteration >= pixelsPerTube)
    {
      currentIteration = 0;
      resetHue += 4;
    }

    nblendPaletteTowardPalette(currentPalette, targetPalette, 24);
    hue = resetHue;

    for (CRGB *ledStrip : ledStrips)
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);

    for (int i = 0; i < dots; i++)
    {
      for (CRGB *ledStrip : ledStrips)
        ledStrip[beatsin16(beatWaveSpeed + i + dots, 0, pixelsPerTube - 1)] += ColorFromPalette(currentPalette, hue);
      hue += 16;
    }

    FastLED.show();
    currentIteration++;

    return 1;
  }

private:
  CRGBPalette16 currentPalette;
  CRGBPalette16 targetPalette;
  uint8_t hue;
  uint8_t dots;
  uint8_t resetHue;
};