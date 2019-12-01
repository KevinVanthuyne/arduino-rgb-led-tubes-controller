#pragma once

#include "menus/Menu.h"
#include "programs/Programs.h"

// globally defined programs from main.cpp
extern ColorCycleProgram colorCycleProgram;
extern ColorCycleSmoothProgram colorCycleSmoothProgram;
extern ColorSweepProgram colorSweepProgram;
extern ColorSweepInToOutProgram colorSweepInToOutProgram;
extern ColorSweepOutToInProgram colorSweepOutToInProgram;
extern ColorSweepInToOutToInProgram colorSweepInToOutToInProgram;
extern SparkleProgram sparkleProgram;
extern RainbowProgram rainbowProgram;
extern BreathingColorCycleSmoothProgram breathingColorCycleSmoothProgram;
extern FadingScanlineProgram fadingScanlineProgram;
extern SparkleColorProgram sparkleColorProgram;
extern StackerProgram stackerProgram;

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
        colorCycleProgram = ColorCycleProgram();
        colorCycleSmoothProgram = ColorCycleSmoothProgram();
        colorSweepProgram = ColorSweepProgram();
        colorSweepInToOutProgram = ColorSweepInToOutProgram();
        colorSweepOutToInProgram = ColorSweepOutToInProgram();
        colorSweepInToOutToInProgram = ColorSweepInToOutToInProgram();
        sparkleProgram = SparkleProgram();
        rainbowProgram = RainbowProgram();
        breathingColorCycleSmoothProgram = BreathingColorCycleSmoothProgram();
        fadingScanlineProgram = FadingScanlineProgram();
        sparkleColorProgram = SparkleColorProgram();
        stackerProgram = StackerProgram();
    }
};