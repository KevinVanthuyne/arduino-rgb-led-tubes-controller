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
  switch (currentProgram)
  {
  // TODO program 0 will cycle through all programs automatically
  case 1:
    iterationDelay = colorCycleProgram.runIteration(programSpeed);
    break;
  case 2:
    iterationDelay = colorCycleSmoothProgram.runIteration(programSpeed);
    break;
  case 3:
    iterationDelay = colorSweepProgram.runIteration(programSpeed);
    break;
  case 4:
    iterationDelay = colorSweepInToOutProgram.runIteration(programSpeed);
    break;
  case 5:
    iterationDelay = colorSweepOutToInProgram.runIteration(programSpeed);
    break;
  case 6:
    iterationDelay = colorSweepInToOutToInProgram.runIteration(programSpeed);
    break;
  case 7:
    iterationDelay = sparkleProgram.runIteration(programSpeed);
    break;
  case 8:
    iterationDelay = rainbowProgram.runIteration(programSpeed);
    break;
  }
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