#include "Input.h"

#include <raylib.h>

#include "Simulation.h"

void handleInput()
{
  if (IsKeyPressed(KEY_EQUAL) && IsKeyDown(KEY_LEFT_SHIFT))
  {
    if (Simulation::timeScale == 1000 || Simulation::timeScale == 1)
      Simulation::timeScale = 10000;
    else
      Simulation::timeScale += Simulation::bigTimeScaleModifier;
  }
  else if (IsKeyPressed(KEY_EQUAL))
  {
    if (Simulation::timeScale == 1)
      Simulation::timeScale = 1000;
    else
      Simulation::timeScale += Simulation::timeScaleModifier;
  }
  else if (IsKeyPressed(KEY_MINUS) && IsKeyDown(KEY_LEFT_SHIFT))
  {
    if (Simulation::timeScale == 10000)
      Simulation::timeScale = 1000;
    else
    {
      if (Simulation::timeScale - Simulation::bigTimeScaleModifier > 0)
        Simulation::timeScale -= Simulation::bigTimeScaleModifier;
      else
        Simulation::timeScale = 1;
    }
  }
  else if (IsKeyPressed(KEY_MINUS))
  {
    if (Simulation::timeScale - Simulation::timeScaleModifier > 0)
      Simulation::timeScale -= Simulation::timeScaleModifier;
    else
      Simulation::timeScale = 1;
  }
  else if (IsKeyPressed(KEY_R))
  {
    Simulation::rotation = !Simulation::rotation;
  }
  else if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_SPACE))
  {
    Simulation::pause = !Simulation::pause;
  }
}
