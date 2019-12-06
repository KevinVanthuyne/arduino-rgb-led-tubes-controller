#pragma once

#include "Globals.h"
#include "programs/Program.h"
#include "Utils.h"

class TheMatrixProgram : public Program
{
public:
  TheMatrixProgram() : Program(), palette(ForestColors_p) {}

  int runIteration(uint8_t speed)
  {
    for (int strip = 0; strip < 6; strip++)
    {
      random16_add_entropy(random());

      // randomly start new letter
      uint8_t randomNumber = random8(90);

      if (randomNumber > 83)
      {
        if (strip == 1 || strip == 4)
        {
          // ledStrips[strip][0] = ColorFromPalette(palette, random16());
          ledStrips[strip][0] = CRGB::Green;
        }
        else if (strip == 2 || strip == 5)
        {
          // ledStrips[strip][pixelsPerTube - 1] = ColorFromPalette(palette, random16());
          ledStrips[strip][pixelsPerTube - 1] = CRGB::Green;
        }
      }
      else
      {
        if (strip == 1 || strip == 4)
          ledStrips[strip][0] = CRGB::Black;
        else if (strip == 2 || strip == 5)
          ledStrips[strip][pixelsPerTube - 1] = CRGB::Black;
      }

      // move everything over
      if (strip == 2 || strip == 5)
        for (int i = 0; i < pixelsPerTube - 1; i++)
          ledStrips[strip][i] = ledStrips[strip][i + 1];
      else if (strip == 1 || strip == 4)
        for (int i = pixelsPerTube - 1; i > 0; i--)
          ledStrips[strip][i] = ledStrips[strip][i - 1];
    }

    FastLED.show();

    return map(speed, 0, 255, 100, 1);
  }

private:
  int previousNumber;
  CRGBPalette16 palette;
};