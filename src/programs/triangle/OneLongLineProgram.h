#pragma once

#include "../../Globals.h"
#include "../Program.h"
#include "../../Utils.h"

class OneLongLineProgram : public Program
{
public:
  OneLongLineProgram() : Program(),
                         currentPos(0),
                         currentColor(random(0, amountOfColors())),
                         previousColor(0),
                         currentStrip(0),
                         stripOrder{0, 1, 2, 5, 4, 3},
                         isFadingOut(false) {}

  int runIteration(uint8_t speed)
  {
    // get the next strip in line
    int strip = stripOrder[currentStrip];

    // color in the strip
    if (isFadingOut)
      ledStrips[strip][currentPos] = CRGB::Black;
    else
      ledStrips[strip][currentPos] = colors[currentColor];

    // first 3 strips are colored start to finish
    if (strip == 0 || strip == 1 || strip == 2)
    {
      currentPos++;

      if (currentPos >= pixelsPerTube)
      {
        currentStrip++;
        if (stripOrder[currentStrip] == 1 || stripOrder[currentStrip] == 2)
          currentPos = 0;
        // when transitioning to the last 3 strips
        else
          currentPos = pixelsPerTube - 1;
      }
    }
    // last 3 strips are colored backwards
    else
    {
      currentPos--;

      if (currentPos < 0)
      {
        currentStrip++;
        if (stripOrder[currentStrip] == 4 || stripOrder[currentStrip] == 3)
          currentPos = pixelsPerTube - 1;
        // when transitioning to the first 3 strips
        else
        {
          currentPos = 0;
          currentStrip = 0;
          strip = stripOrder[0];
          if (isFadingOut)
          {
            previousColor = currentColor;
            currentColor = getRandomNumber(0, amountOfColors(), previousColor);
          }
          isFadingOut = !isFadingOut;
        }
      }
    }

    FastLED.show();

    return map(speed, 0, 255, 50, 1);
  }

private:
  uint8_t hue;
  int currentPos;
  int currentColor;
  int previousColor;
  int currentStrip;
  int stripOrder[6];
  bool isFadingOut;
};