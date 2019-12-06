#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class LightningProgram : public Program
{
public:
  LightningProgram() : Program(),
                       flashes(8),
                       dimmer(1) {}

  int runIteration(uint8_t speed)
  {
    // for (CRGB *ledStrip : ledStrips)
    // {
    //   fill_solid(ledStrip, pixelsPerTube, colors[number]);
    // }

    int lightningChance = map(speed, 0, 255, 250, 120);

    // random chance for a lighting strike to go off
    if (random8() > lightningChance)
    {
      int strip = random8(5);                      // choose a random strip
      int start = random8(pixelsPerTube);          // Determine starting location of flash
      int length = random8(pixelsPerTube - start); // Determine length of flash (not to go beyond NUM_LEDS-1)

      for (int flashCounter = 0; flashCounter < random8(3, flashes); flashCounter++)
      {
        if (flashCounter == 0)
          dimmer = 5; // the brightness of the leader is scaled down by a factor of 5
        else
          dimmer = random8(1, 3); // return strokes are brighter than the leader

        fill_solid(ledStrips[strip] + start, length, CHSV(255, 0, 255 / dimmer));
        FastLED.show(); // Show a section of LED's

        delay(random8(4, 10));                                         // each flash only lasts 4-10 milliseconds
        fill_solid(ledStrips[strip] + start, length, CHSV(255, 0, 0)); // Clear the section of LED's
        FastLED.show();

        if (flashCounter == 0)
          delay(150); // longer delay until next flash after the leader

        delay(50 + random8(100)); // shorter delay between strokes
      }                           // for()
    }

    return 1;
  }

private:
  int flashes;
  int dimmer;
};