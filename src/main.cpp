#include <vector>

#include "CelestialBody.h"
#include "SolarSystem.h"
#include "Window.h"

int main()
{
  std::vector<CelestialBody> SolarSystem = getSolarSystem();
  Celestial::sort(SolarSystem);
  Celestial::setBounds(SolarSystem);

  float elapsedTime = 0.0f;

  Window window(SolarSystem);
  while(window.Open())
  {
    window.Update(elapsedTime);
  }
}
