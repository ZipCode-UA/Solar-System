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

  static double smallestRadius;
  static double smallestOrbitRadius;
  static double greatestRadius;
  static double greatestOrbitRadius;
  static double scaleTargetMinRadiusSize;
  static double scaleTargetMaxRadiusSize;
  static double scaleTargetMinOrbitRadiusSize;
  static double scaleTargetMaxOrbitRadiusSize;
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
  CelestialBody() = default;
  CelestialBody(const std::string& name, const std::string& fileName, double mass, double volume, double density, double gravity, double radius, double velocity, double perihelion, double aphelion, double orbitRotation, double axisRotation, int satellites, bool ring);
  CelestialBody(const CelestialBody&) = default;
  CelestialBody& operator=(CelestialBody&&) = default;
  ~CelestialBody() = default;

private:
  double logScale(double value, const std::string& type) const;

public:
  double getDistance(const CelestialBody& compare) const;
  double getDistance(const CelestialBody& compare, double uptime) const;
  double getAttractionForce(const CelestialBody& compare, double uptime) const;

public:
  // Accessors
  std::string getName() const { return name; }
  std::string getFileName() const { return fileName; }
  double getMass() const { return mass; }
  double getVolume() const { return volume; }
  double getDensity() const { return density; }
  double getGravity() const { return gravity; }
  double getRadius() const { return logScale(radius, "radius"); }
  double getUnscaledRadius() const { return radius; }
  double getVelocity() const { return velocity; }
  double getPerihelion() const { return perihelion; }
  double getAphelion() const { return aphelion; }
  double getOrbitRotation() const { return orbitRotation; }
  double getOrbitRadius() const { return logScale(orbitRadius, "orbitRadius"); }
  double getUnscaledOrbitRadius() const { return orbitRadius; }
  double getOrbitPosition() const { return orbitPosition; }
  double getAxisRotation() const { return axisRotation; }
  double getAxisPosition() const { return axisPosition; }
  int getSatellites() const { return satellites; }
  bool getRing() const { return ring; }

public:
  // Mutators
  void updateOrbitPosition(double pi, double timeScale);
  void updateAxisPosition(double pi, double timeScale);
  void setOrbitPosition(double orbitPosition) { this->orbitPosition = orbitPosition; }
  void setAxisPosition(double axisPosition) { this->axisPosition = axisPosition; }
  void setSatellites(int satellites) { this->satellites = satellites; }

private: 
  std::string name;
  std::string fileName;
  double mass = 0;
  double volume = 0;
  double density = 0;
  double gravity = 0;
  double radius = 0;
  double velocity = 0;
  double perihelion = 0;
  double aphelion = 0;
  double orbitRotation = 0;
  double orbitRadius = 0;
  double orbitPosition = 0;
  double axisRotation = 0;
  double axisPosition = 0;
  int satellites = 0;
  bool ring = false;
};

#endif // CELESTIALBODY_H
