#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/Menu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

class AutoMode : public Mode
{
public:
  AutoMode() {}
  AutoMode(Menu *menu) : Mode(menu),
                         iterationDelay(200),
                         newProgramDelay(0),
                         previousIterationMillis(0),
                         previousProgramMillis(0)
  {
  }
  void runIteration();

private:
  unsigned long iterationDelay;
  unsigned long newProgramDelay;
  unsigned long previousIterationMillis;
  unsigned long previousProgramMillis;
  void runProgram();
  void newProgram();
};