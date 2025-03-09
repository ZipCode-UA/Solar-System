#include <vector>

#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Window.h"

int main()
{
  std::vector<CelestialBody> SolarSystem = getSolarSystem();
  Celestial::sort(SolarSystem);
  Celestial::setBounds(SolarSystem);

  Window window(SolarSystem);
  while(window.Open())
  {
    window.Update();
  }
}
