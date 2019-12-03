#include "Utils.h"

void noop()
{
    return;
}

int getRandomNumber(int min, int max)
{
    return random(min, max + 1);
}

// get a random number that is not equal to the previous one
int getRandomNumber(int min, int max, int previousNumber)
{
    int number;
    do
    {
        number = getRandomNumber(min, max);
    } while (number == previousNumber);
    return number;
}

// Blend one CRGB color toward another CRGB color by a given amount (N/256).
// Blending is linear, and done in the RGB color space.
// modifies currentColor in place
CRGB fadeTowardColor(CRGB &currentColor, const CRGB targetColor, uint8_t amount)
{
    nblendU8TowardU8(currentColor.red, targetColor.red, amount);
    nblendU8TowardU8(currentColor.green, targetColor.green, amount);
    nblendU8TowardU8(currentColor.blue, targetColor.blue, amount);
    return currentColor;
}

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8(uint8_t &current, const uint8_t target, uint8_t amount)
{
    if (current == target)
        return;

    if (current < target)
    {
        uint8_t delta = target - current;
        delta = scale8_video(delta, amount);
        current += delta;
    }
    else
    {
        uint8_t delta = current - target;
        delta = scale8_video(delta, amount); // TODO: is normal scale8 better?
        current -= delta;
    }
}
