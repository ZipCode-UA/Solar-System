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

/**
  Calculates the approximate distance between two celestial bodies. This is only an average distance, as real orbits are elliptical.

  @param a - The first celestial body.
  @param b - The second celestial body.
  @return The distance between the two celestial bodies.
*/
double CelestialBody::getDistance(const CelestialBody& compare) const
{
  double meanDistanceA = (perihelion + aphelion) / 2;
  double meanDistanceB = (compare.getPerihelion() + compare.getAphelion()) / 2;

  return fabs(meanDistanceA - meanDistanceB);
}

//TODO: Implement this function in its entirety - missing time parameter
/**
  Calculates a more accurate distance between two celestial bodies
  Assumptions: 
  - Time is fixed in this function
  - The celestial bodies are in the same plane
  - Constant angular velocity

  @param a - The first celestial body.
  @param b - The second celestial body.
  @return The distance between the two celestial bodies.
*/

/*
double CelestialBody::getDistance(const CelestialBody& compare) const
{

  const double PI = 3.14159265358979323846;

  //semi major axis calculation
  double meanDistanceA = (perihelion + aphelion) / 2;
  double meanDistanceB = (compare.getPerihelion() + compare.getAphelion()) / 2;

  //orbital eccentricity calculation
  double eccentricityA = (aphelion - perihelion) / (aphelion + perihelion);
  double eccentricityB = (compare.getAphelion() - compare.getPerihelion()) / (compare.getAphelion() + compare.getPerihelion());

  //true anomaly calculation (approximation)
  //TODO: Implement a more accurate calculation
  //TODO: Use current program time to calculate the true anomaly - time is currently hardcoded
  double time = 60; //time in days
  double thetaA = 2 * PI * time / orbit();
  double thetaB = 2 * PI * time / compare.getOrbit();

  //Radial distance calculation -- using orbit equation
  double radialA = (meanDistanceA * (1 - pow(eccentricityA, 2))) / (1 + eccentricityA * cos(thetaA));
  double radialB = (meanDistanceB * (1 - pow(eccentricityB, 2))) / (1 + eccentricityB * cos(thetaB));

  //x-y coordinates calculation
  double xA = radialA * cos(thetaA);
  double yA = radialA * sin(thetaA);
  double xB = radialB * cos(thetaB);
  double yB = radialB * sin(thetaB);

  //distance calculation -- using distance formula
  return sqrt(pow(xA - xB, 2) + pow(yA - yB, 2));
}
*/

double CelestialBody::getAttractionForce(const CelestialBody& compare) const
{
  const double gravitationalForce = 6.6743 * pow(10, -11); // m^3/kg^2
  const double distance = getDistance(compare);
  
  return gravitationalForce * ((mass * compare.getMass()) / (pow(distance, 2)));
}
