#include "SolarSystem.h"

#include <cmath>
#include <vector>

#include "CelestialBody.h"
#include "MilkyWay.h"

int main()
{
  std::vector<CelestialBody> MilkyWay = getMilkyWay();
}

double getDistance(const CelestialBody &a, const CelestialBody &b)
{
  // TODO - Calculate distance from the central point between objects a and b
  double distance = 0; // km

  return distance;
}

double getAttractionForce(const CelestialBody &a, const CelestialBody &b)
{
  const double gravitationalForce = 6.6743 * pow(10, -11); // m^3/kg^2
  const double distance = getDistance(a, b);
  
  return gravitationalForce * ((a.getMass() * b.getMass()) / (pow(distance, 2)));
}
