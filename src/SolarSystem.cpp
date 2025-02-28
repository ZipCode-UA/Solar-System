#include "SolarSystem.h"

#include <cmath>
#include <vector>

#include "CelestialBody.h"
#include "MilkyWay.h"

// TODO: Move this to GUI.cpp
// int main()
// {
//   std::vector<CelestialBody> MilkyWay = getMilkyWay();
// }


/**
  Calculates the approximate distance between two celestial bodies. This is only an average distance, as real orbits are elliptical.

  @param a - The first celestial body.
  @param b - The second celestial body.
  @return The distance between the two celestial bodies.
*/
double getDistance(const CelestialBody &a, const CelestialBody &b)
{
  double meanDistanceA = (a.getPerihelion() + a.getAphelion()) / 2;
  double meanDistanceB = (b.getPerihelion() + b.getAphelion()) / 2;

  return fabs(meanDistanceA - meanDistanceB);
}

double getAttractionForce(const CelestialBody &a, const CelestialBody &b)
{
  const double gravitationalForce = 6.6743 * pow(10, -11); // m^3/kg^2
  const double distance = getDistance(a, b);
  
  return gravitationalForce * ((a.getMass() * b.getMass()) / (pow(distance, 2)));
}
