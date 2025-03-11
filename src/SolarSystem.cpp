#include "SolarSystem.h"

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

std::vector<CelestialBody> getSolarSystem()
{
  std::vector<CelestialBody> SolarSystem;

  CelestialBody Sun
  (
    "Sun",
    "Sun.jpg",
    1.989       * pow(10, 30),
    1.412       * pow(10, 18),
    1408,
    274,
    6.957       * pow(10, 5),
    0,
    0,
    0,
    0,
    0,
    false
  );
  SolarSystem.push_back(Sun);

  CelestialBody Mercury
  (
    "Mercury",
    "Mercury.jpg",
    0.3301      * pow(10, 24),
    6.083       * pow(10, 10),
    5.429       * pow(10, 3),
    3.70,
    2.4397      * pow(10, 3),
    4.736       * pow(10, 1),
    4.6000      * pow(10, 7),
    6.9818      * pow(10, 7),
    8.7969      * pow(10, 1),
    0,
    false
  );
  SolarSystem.push_back(Mercury);

  CelestialBody Venus
  (
    "Venus",
    "Venus.jpg",
    4.8673        * pow(10, 24),
    9.2843        * pow(10, 11),
    5.243         * pow(10, 3),
    8.87,
    6.0518        * pow(10, 3),
    3.502 * 10,
    1.07480       * pow(10, 8),
    1.08941       * pow(10, 8),
    2.24701       * pow(10, 2),
    0,
    false
  );
  SolarSystem.push_back(Venus);

  CelestialBody Earth
  (
    "Earth",
    "Earth.jpg",
    5.9722      * pow(10, 24),
    1.08321     * pow(10, 12),
    5.513       * pow(10, 3),
    9.82,
    6.371       * pow(10, 3),
    2.978       * pow(10, 1),
    1.47095     * pow(10, 8),
    1.52100     * pow(10, 8),
    3.65256     * pow(10, 2),
    1,
    false
  );
  SolarSystem.push_back(Earth);

  CelestialBody Mars
  (
    "Mars",
    "Mars.jpg",
    6.4159      * pow(10, 23),
    1.6312      * pow(10, 11),
    3.934       * pow(10, 3),
    3.73,
    3.3895      * pow(10, 3),
    2.408       * pow(10, 1),
    2.06650     * pow(10, 8),
    2.49261     * pow(10, 8),
    6.86980     * pow(10, 2),
    2,
    false
  );
  SolarSystem.push_back(Mars);

  CelestialBody Jupiter
  (
    "Jupiter",
    "Jupiter.jpg",
    1.89813     * pow(10, 27),
    1.43128     * pow(10, 15),
    1.326       * pow(10, 3),
    2.592       * pow(10, 1),
    6.9911      * pow(10, 4),
    1.306       * pow(10, 1),
    7.40595     * pow(10, 8),
    8.16363     * pow(10, 8),
    4.33259     * pow(10, 3),
    9.5         * pow(10, 1),
    true
  );
  SolarSystem.push_back(Jupiter);

  CelestialBody Saturn
  {
    "Saturn",
    "Saturn.jpg",
    5.6832      * pow(10, 26),
    8.2713      * pow(10, 14),
    687,
    11.19,
    5.8232      * pow(10,4),
    9.67,
    1.357554    * pow(10, 9),
    1.506527    * pow(10, 9),
    1.075699    * pow(10, 4),
    146,
    true
  };
  SolarSystem.push_back(Saturn);

  CelestialBody Uranus
  (
    "Uranus",
    "Uranus.jpg",
    8.6811      * pow(10, 24),
    6.833       * pow(10, 13),
    1.270       * pow(10, 3),
    9.01,
    2.5362      * pow(10, 4),
    6.79,
    2.732696    * pow(10, 9),
    3.00139     * pow(10, 9),
    3.06854     * pow(10, 4),
    2.8         * pow(10, 1),
    true
  );
  SolarSystem.push_back(Uranus);

  CelestialBody Neptune
  (
    "Neptune",
    "Neptune.jpg",
    1.02409     * pow(10, 26),
    6.254       * pow(10, 13),
    1.638       * pow(10, 3),
    1.127       * pow(10, 1),
    2.4622      * pow(10, 4),
    5.45,
    4.471050    * pow(10, 9),
    4.558857    * pow(10, 9),
    6.0189018   * pow(10, 4),
    1.6         * pow(10, 1),
    true
  );
  SolarSystem.push_back(Neptune);

  CelestialBody Pluto
  (
    "Pluto",
    "Pluto.jpg",
    1.303     * pow(10, 22),
    7.02      * pow(10, 9),
    1.854     * pow(10, 3),
    6.2       * pow(10, -1),
    1.188     * pow(10, 3),
    4.64,
    4.434987  * pow(10, 9),
    7.304326  * pow(10, 9),
    9.05609   * pow(10, 5),
    5,
    false
  );
  SolarSystem.push_back(Pluto);

  // TODO - Add Chiron :) ...Pls put it in sci notation like above

  return SolarSystem;
}
