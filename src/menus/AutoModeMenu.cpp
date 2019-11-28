#include "AutoModeMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine autoModeLine(1, 0, "AUTO MODE");
LiquidLine autoModeProgramLine(2, 1, "Program: ", currentProgram);
LiquidLine autoModeSpeedLine(2, 2, "Speed: ", programSpeed);
LiquidScreen autoModeScreen(autoModeLine, autoModeProgramLine, autoModeSpeedLine);

AutoModeMenu::AutoModeMenu()
{
  autoModeScreen.set_focusPosition(Position::LEFT);
  autoModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
  autoModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
  liquidMenu.add_screen(autoModeScreen);
}