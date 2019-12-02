#pragma once

#include "menus/Menu.h"
#include "programs/Programs.h"

// Abstract class for other Modes to derive from
class Mode
{
public:
    Mode() {}
    virtual ~Mode() {}
    virtual void runIteration() = 0;
    // To be implememented when more modes are added
    // virtual void changeToStaticMode() = 0;
    // virtual void changeToAutoMode() = 0;
    // virtual void changeToSoundMode() = 0;
    Menu *menu;

protected:
    Mode(Menu *menu) : menu(menu)
    {
    }
};