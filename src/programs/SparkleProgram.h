#pragma once

#include "Program.h"
#include "../Utils.h"

class SparkleProgram : public Program
{
public:
    SparkleProgram() : Program() {}
    int runIteration(uint8_t speed)
    {
        for (CRGB *ledStrip : ledStrips)
        {
            int fadeSpeed = map(speed, 0, 255, 2, 10);
            fadeToBlackBy(ledStrip, pixelsPerTube, fadeSpeed);

            int newSparkleSpeed = map(speed, 0, 255, 16, 2);
            if (currentIteration % newSparkleSpeed == 0)
            {
                int pos = random16(pixelsPerTube);
                for (int i = 0; i < 2; i++)
                    if (pos + i < pixelsPerTube - 1)
                        ledStrip[pos + i] += CRGB::White;
            }
        }
        FastLED.show();
        currentIteration++;

        return 1;
    }
};