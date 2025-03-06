#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <vector>

class CelestialBody;

namespace Celestial
{
  // TODO: Add to CelestialBody class as static members
  void sort(std::vector<CelestialBody>& SolarSystem);
  void setBounds(const std::vector<CelestialBody>& SolarSystem);

  void setSmallestRadius(const std::vector<CelestialBody>& SolarSystem);
  void setSmallestOrbitRadius(const std::vector<CelestialBody>& SolarSystem);
  void setGreatestRadius(const std::vector<CelestialBody>& SolarSystem);
  void setGreatestOrbitRadius(const std::vector<CelestialBody>& SolarSystem);

  const double scaleTargetMinRadiusSize = 1;
  const double scaleTargetMaxRadiusSize = 100;
  static double smallestRadius;
  static double smallestOrbitRadius;
  static double greatestRadius;
  static double greatestOrbitRadius;
}

class CelestialBody
{
private:
  // TODO: Add to CelestialBody class as static members
  friend void Celestial::setSmallestRadius(const std::vector<CelestialBody>& SolarSystem);
  friend void Celestial::setSmallestOrbitRadius(const std::vector<CelestialBody>& SolarSystem);
  friend void Celestial::setGreatestRadius(const std::vector<CelestialBody>& SolarSystem);
  friend void Celestial::setGreatestOrbitRadius(const std::vector<CelestialBody>& SolarSystem);

public:
  CelestialBody(const std::string& name, double mass, double volume, double density, double gravity, double radius, double velocity, double perihelion, double aphelion, double orbit, int satellites, bool ring);
  ~CelestialBody() { };

private:
  double logScale(double value) const;
  double linearScale(double value) const;

public:
  double getDistance(const CelestialBody& compare) const;
  double getAttractionForce(const CelestialBody& compare) const;

public:
  // Accessors
  std::string getName() const { return this->name; }
  double getMass() const { return this->mass; }
  double getVolume() const { return this->volume; }
  double getDensity() const { return this->density; }
  double getGravity() const { return this->gravity; }
  double getRadius() const { return logScale(this->radius); }
  double getVelocity() const { return this->velocity; }
  double getPerihelion() const { return this->perihelion; }
  double getAphelion() const { return this->aphelion; }
  double getOrbit() const { return this->orbit; }
  double getOrbitRadius() const { return linearScale(this->orbitRadius); }
  int getSatellites() const { return this->satellites; }
  bool getRing() const { return this->ring; }

private: 
  const std::string name;
  const double mass;
  const double volume;
  const double density;
  const double gravity;
  const double radius;
  const double velocity;
  const double perihelion;
  const double aphelion;
  const double orbit;
  const double orbitRadius;
  const int satellites;
  const bool ring;
};

#endif // CELESTIALBODY_H
