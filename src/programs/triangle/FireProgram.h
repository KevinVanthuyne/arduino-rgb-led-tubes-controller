#pragma once

#include "../../Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class FireProgram : public Program
{
public:
  FireProgram() : Program(),
                  palette(HeatColors_p),
                  // SPARKING: What chance (out of 255) is there that a new spark will be lit?
                  // Higher chance = more roaring fire.  Lower chance = more flickery fire.
                  // Default 120, suggested range 50-200.
                  sparking(135),
                  // COOLING: How much does the air cool as it rises?
                  // Less cooling = taller flames.  More cooling = shorter flames.
                  // Default 55, suggested range 20-100
                  cooling(60),
                  reverseDirection(false)
  {
    for (int i = 0; i < pixelsPerTube; i++)
      heat[i] = 0;
  }

  int runIteration(uint8_t speed)
  {
    random16_add_entropy(random());

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < pixelsPerTube; i++)
    {
      heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / pixelsPerTube) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = pixelsPerTube - 1; k >= 2; k--)
    {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < sparking)
    {
      int y = random8(7);
      heat[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for (int j = 0; j < pixelsPerTube; j++)
    {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8(heat[j], 240);
      CRGB color = ColorFromPalette(palette, colorindex);
      int pixelnumber;
      if (reverseDirection)
      {
        pixelnumber = (pixelsPerTube - 1) - j;
      }
      else
      {
        pixelnumber = j;
      }
      ledStrips[1][pixelsPerTube - 1 - pixelnumber] = color;
      ledStrips[2][pixelnumber] = color;
      ledStrips[4][pixelsPerTube - 1 - pixelnumber] = color;
      ledStrips[5][pixelnumber] = color;
    }

    FastLED.show();

    return 1;
  }

private:
  CRGBPalette16 palette;
  byte heat[58];
  int sparking;
  int cooling;
  bool reverseDirection;
};