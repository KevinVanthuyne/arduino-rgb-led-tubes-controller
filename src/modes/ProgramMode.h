#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/Menu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

class ProgramMode : public Mode
{
public:
    ProgramMode() {}
    ProgramMode(Menu *menu) : Mode(menu), iterationDelay(200), previousIterationMillis(0)
    {
    }
    void runIteration();

private:
    unsigned long iterationDelay;
    unsigned long previousIterationMillis;
};