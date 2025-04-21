#include "Simulation.h"

int main()
{
  Simulation simulation;
  while (simulation.running)
  {
    simulation.update();
  }
}
