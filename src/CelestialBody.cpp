#include "CelestialBody.h"

#include <cmath>
#include <string>

namespace Celestial
{
  // TODO: Sort vector by orbitRadius from least to highest
  void sort(std::vector<CelestialBody>& SolarSystem)
  {

  }
  
  void setBounds(const std::vector<CelestialBody>& SolarSystem)
  {
    setSmallestRadius(SolarSystem);
    setSmallestOrbitRadius(SolarSystem);
    setGreatestRadius(SolarSystem);
    setGreatestOrbitRadius(SolarSystem);
  }
  
  void setSmallestRadius(const std::vector<CelestialBody>& SolarSystem)
  {
    double smallest = SolarSystem[0].radius;
  
    for (const auto iter : SolarSystem)
      if (iter.radius < smallest)
        smallest = iter.radius; 
  
    smallestRadius = smallest;
  }
  
  void setSmallestOrbitRadius(const std::vector<CelestialBody>& SolarSystem)
  {
    double smallest = SolarSystem[1].orbitRadius;
  
    for (const auto iter : SolarSystem)
      if (iter.orbitRadius < smallest && iter.orbitRadius != 0)
        smallest = iter.orbitRadius; 
  
    smallestOrbitRadius = smallest;
  }
  
  void setGreatestRadius(const std::vector<CelestialBody>& SolarSystem)
  {
    double greatest = SolarSystem[0].radius;
  
    for (const auto iter : SolarSystem)
      if (iter.radius > greatest)
        greatest = iter.radius; 
  
    greatestRadius = greatest;
  }
  
  void setGreatestOrbitRadius(const std::vector<CelestialBody>& SolarSystem)
  {
    double greatest = SolarSystem[0].orbitRadius;
  
    for (const auto iter : SolarSystem)
      if (iter.orbitRadius > greatest)
        greatest = iter.orbitRadius; 
  
    greatestOrbitRadius = greatest;
  }
}

CelestialBody::CelestialBody(const std::string& name, double mass, double volume, double density, double gravity, double radius, double velocity, double perihelion, double aphelion, double orbit, int satellites, bool ring)
  : name(name),
    mass(mass),
    volume(volume),
    density(density),
    gravity(gravity),
    radius(radius),
    velocity(velocity),
    perihelion(perihelion),
    aphelion(aphelion),
    orbit(orbit),
    orbitRadius((perihelion + aphelion) / 2),
    satellites(satellites),
    ring(ring) { }

double CelestialBody::logScale(double value) const
{
  if (value == 0)
    return 0;

  double logValue = log(value);
  double logSmallest = log(Celestial::smallestRadius);
  double logGreatest = log(Celestial::greatestRadius);

  return Celestial::scaleTargetMinRadiusSize + (((logValue - logSmallest) / (logGreatest - logSmallest)) * (Celestial::scaleTargetMaxRadiusSize - Celestial::scaleTargetMinRadiusSize));
}

double CelestialBody::linearScale(double value) const
{
  if (value == 0)
    return 0;

  double scaleTargetMinOrbitRadiusSize = Celestial::scaleTargetMaxRadiusSize + Celestial::scaleTargetMinRadiusSize;
  double scaleTargetMaxOrbitRadiusSize = scaleTargetMinOrbitRadiusSize * 5;

  double smallest = Celestial::smallestOrbitRadius;
  double greatest = Celestial::greatestOrbitRadius;

  return scaleTargetMinOrbitRadiusSize + (((value - smallest) / (greatest - smallest)) * (scaleTargetMaxOrbitRadiusSize - scaleTargetMinOrbitRadiusSize));
}

double CelestialBody::getDistance(const CelestialBody& compare) const
{
  // TODO - Calculate distance from the central point between objects a and b
  double distance = 0; // km

  return distance;
}

double CelestialBody::getAttractionForce(const CelestialBody& compare) const
{
  const double gravitationalForce = 6.6743 * pow(10, -11); // m^3/kg^2
  const double distance = getDistance(compare);
  
  return gravitationalForce * ((mass * compare.getMass()) / (pow(distance, 2)));
}
