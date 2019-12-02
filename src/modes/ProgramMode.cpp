#include "ProgramMode.h"

void ProgramMode::runIteration()
{
    unsigned long currentMillis = millis();

    // only runs an iteration of the program when the required delay has passed
    if (currentMillis - previousIterationMillis >= iterationDelay)
    {
        previousIterationMillis = currentMillis;
        iterationDelay = programs[currentProgram - 1]->runIteration(programSpeed);
    }
}