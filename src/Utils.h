#pragma once

#include <Arduino.h>
#include "FastLED.h"

void noop();
int getRandomNumber(int min, int max);
int getRandomNumber(int min, int max, int previousNumber);
CRGB fadeTowardColor(CRGB &currentColor, const CRGB targetColor, uint8_t amount);
void nblendU8TowardU8(uint8_t &current, const uint8_t target, uint8_t amount);
