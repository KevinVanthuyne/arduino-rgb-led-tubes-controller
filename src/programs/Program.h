#pragma once

#include "../Utils.h"

extern CRGB *ledStrips[6]; // globally defined ledtubes
extern byte pixelsPerTube;

class Program
{
public:
    Program() : currentIteration(0) {}
    virtual ~Program() {}
    // runs a single iteration of the program/animation and returns the required wait time
    virtual int runIteration(uint8_t speed) = 0;

protected:
    unsigned int currentIteration;

    // colors
    CRGB colors[9] = {
        CRGB(255, 0, 0),   // red
        CRGB(255, 128, 0), // orange
        CRGB(255, 255, 0), // yellow
        CRGB(0, 255, 0),   // green
        CRGB(0, 255, 128), // cyan
        CRGB(0, 128, 255), // light blue
        CRGB(0, 0, 255),   // blue
        CRGB(128, 0, 255), // purple
        CRGB(255, 0, 255), // pink
    };
};