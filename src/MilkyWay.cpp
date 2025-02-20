#include "MilkyWay.h"

#include <cmath>
#include <vector>

#include "CelestialBody.h"

/**
  Planetary data pulled from:
  https://nssdc.gsfc.nasa.gov/planetary/planetfact.html

  Measurements:
  mass - kg
  volume - km^3
  radius - km
  density - kg/m^3
  velocity - km/s
  orbit - days
  gravity - m/s^2
  perihelion - km
  aphelion - km

  Context:
  radius - volumetric mean radius
  density - mean density
  velocity - mean orbital velocity
  gravity - surface gravity
  perihelion - closest distance from sun
  aphelion - furthest distance from sun
*/

std::vector<CelestialBody> getMilkyWay()
{
  std::vector<CelestialBody> MilkyWay;

  CelestialBody Sun
  (
    1.989 * pow(10, 30),
    1.412 * pow(10, 18),
    6.957 * pow(10, 5),
    1408,
    0,
    0,
    274,
    0,
    0,
    0,
    false
  );
  MilkyWay.push_back(Sun);

  // TODO - Add Mercury

  // TODO - Add Venus

  CelestialBody Earth
  (
    5.9722 * pow(10, 24),
    108.321 * pow(10, 10),
    6371,
    5513,
    29.78,
    365.256,
    9.82,
    147.095 * pow(10, 6),
    152.100 * pow(10, 6),
    1,
    false
  );
  MilkyWay.push_back(Earth);
  
  CelestialBody Mars
  (
    6.4159 * pow(10, 23),
    16.312 * pow(10, 10),
    3389.5,
    3934,
    24.08,
    686.980,
    3.73,
    206.650 * pow(10, 6),
    249.261 * pow(10, 6),
    2,
    false
  );
  MilkyWay.push_back(Mars);

  // TODO - Add Jupiter

  // TODO - Add Saturn

  // TODO - Add Uranus
  
  // TODO - Add Neptune

  // TODO - Add Pluto :)

  // TODO - Add Chiron :)

  return MilkyWay;
}
