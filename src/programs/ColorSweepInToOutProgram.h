#pragma once

#include "Program.h"
#include "../Utils.h"

class ColorSweepInToOutProgram : public Program
{
public:
    ColorSweepInToOutProgram() : Program(), currentColor(CRGB::Red), previousNumber(-1) {}
    int runIteration(uint8_t speed)
    {
        unsigned int center = (unsigned int)floor(pixelsPerTube / 2);

        if (currentIteration > center)
        {
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
        }

        for (CRGB *ledStrip : ledStrips)
        {
            if ((center + currentIteration) < pixelsPerTube) // prevents setting a pixel just outside of the strip
                ledStrip[center + currentIteration] = currentColor;
            ledStrip[center - currentIteration] = currentColor;
        }
        FastLED.show();

        currentIteration++;
        return map(speed, 0, 255, 100, 5);
    }

private:
    CRGB currentColor;
    int previousNumber;
};