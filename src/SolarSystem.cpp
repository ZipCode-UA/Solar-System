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
double getDistance(const CelestialBody &a, const CelestialBody &b)
{

  const double PI = 3.14159265358979323846;

  //semi major axis calculation
  double meanDistanceA = (a.getPerihelion() + a.getAphelion()) / 2;
  double meanDistanceB = (b.getPerihelion() + b.getAphelion()) / 2;

  //orbital eccentricity calculation
  double eccentricityA = (a.getAphelion() - a.getPerihelion()) / (a.getAphelion() + a.getPerihelion());
  double eccentricityB = (b.getAphelion() - b.getPerihelion()) / (b.getAphelion() + b.getPerihelion());

  //true anomaly calculation (approximation)
  //TODO: Implement a more accurate calculation
  //TODO: Use current program time to calculate the true anomaly - time is currently hardcoded
  double time = 60; //time in days
  double thetaA = 2 * PI * time / a.getOrbit();
  double thetaB = 2 * PI * time / b.getOrbit();

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