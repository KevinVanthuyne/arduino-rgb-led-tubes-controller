#pragma once

#include "Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class RotorFadeProgram : public Program
{
public:
  RotorFadeProgram() : Program(),
                       hue(getRandomNumber(0, 255)),
                       currentStrip(0),
                       stripOrder{0, 2, 5, 3} {}

  int runIteration(uint8_t speed)
  {
    int lightUpInterval = map(speed, 0, 255, 80, 10);
    int fadeSpeed = map(speed, 0, 255, 1, 10);

    // fade everything out slowly
    for (CRGB *ledStrip : ledStrips)
    {
      fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);
    }

    // light up the next strip after a certain interval
    if (currentIteration % lightUpInterval == 0)
    {
      // if the last strip is reached, start over
      if (currentStrip >= (sizeof(stripOrder) / sizeof(stripOrder[0])))
        currentStrip = 0;

      // light up the correct strip according to the order
      int strip = stripOrder[currentStrip];
      fill_solid(ledStrips[strip], pixelsPerTube, CHSV(hue, 255, 255));

      currentStrip++;
      hue += 2;
    }

    FastLED.show();
    currentIteration++;

    return 1;
  }

private:
  uint8_t hue;
  unsigned int currentStrip;
  int stripOrder[4];
};