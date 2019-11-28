#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/AutoMenu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

class AutoMode : public Mode
{
public:
    AutoMode() {}
    AutoMode(Menu *menu) : Mode(menu), iterationDelay(200), previousIterationMillis(0)
    {
    }
    void runIteration();

private:
    unsigned long iterationDelay;
    unsigned long previousIterationMillis;
};