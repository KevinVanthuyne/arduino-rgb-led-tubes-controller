#include "AutoMode.h"

void AutoMode::runIteration()
{
  unsigned long currentMillis = millis();

  // only runs an iteration of the program when the required delay has passed
  if (currentMillis - previousIterationMillis >= iterationDelay)
  {
    previousIterationMillis = currentMillis;
    runProgram();
  }

  // change the program if it has ran long enough
  if (currentMillis - previousProgramMillis >= newProgramDelay)
  {
    previousProgramMillis = currentMillis;
    newProgram();
  }
}

void AutoMode::runProgram()
{
  iterationDelay = programs[currentProgram - 1]->runIteration(programSpeed);
}

void AutoMode::newProgram()
{
  programSpeed = random(64, 128);
  int amountOfPrograms = (sizeof(allowedPrograms) / sizeof(allowedPrograms[0]));
  int newProgramIndex = getRandomNumber(0, amountOfPrograms - 1);
  currentProgram = allowedPrograms[newProgramIndex];
  newProgramDelay = getRandomNumber(15, 60) * 1000;
  liquidMenu.update();
  Serial.println("Changed program");
}