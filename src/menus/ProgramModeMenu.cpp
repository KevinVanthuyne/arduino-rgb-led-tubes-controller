#include "ProgramModeMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine programModeLine(1, 0, "PROGRAM MODE");
LiquidLine programLine(2, 1, "Program: ", currentProgram);
LiquidLine speedLine(2, 2, "Speed: ", programSpeed);
LiquidScreen programModeScreen(programModeLine, programLine, speedLine);

// callback functions for the menu
void increaseCurrentProgram()
{
    if (currentProgram < sizeof(programs) / sizeof(programs[0]))
        currentProgram++;
    else if (currentProgram == sizeof(programs) / sizeof(programs[0]))
        currentProgram = 1;

    FastLED.clear();
}

void decreaseCurrentProgram()
{
    if (currentProgram > 1)
        currentProgram--;
    else if (currentProgram == 1)
        currentProgram = sizeof(programs) / sizeof(programs[0]);

    FastLED.clear();
}

void increaseSpeed()
{
    // TODO steps of 1 on short press, bigger steps on long press
    if (programSpeed < 255 - 31)
        programSpeed += 31;
}

void decreaseSpeed()
{
    if (programSpeed > 31)
        programSpeed -= 31;
}

ProgramModeMenu::ProgramModeMenu()
{
    programModeScreen.set_focusPosition(Position::LEFT);
    programModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
    programModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
    programLine.attach_function(RIGHT_PRESS, increaseCurrentProgram);
    programLine.attach_function(LEFT_PRESS, decreaseCurrentProgram);
    speedLine.attach_function(RIGHT_PRESS, increaseSpeed);
    speedLine.attach_function(LEFT_PRESS, decreaseSpeed);
    liquidMenu.add_screen(programModeScreen);
}