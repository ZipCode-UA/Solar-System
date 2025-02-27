#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <string>

class CelestialBody
{ 
private: 
  std::string name;
  double mass;
  double volume;
  double radius;
  double density;
  double velocity;
  double orbit;
  double gravity;
  double perihelion;
  double aphelion;
  int satellites;
  bool ring;

public:
  CelestialBody(const char* name, double mass, double volume, double radius, double density, double velocity, double orbit, double gravity, double perihelion, double aphelion, int satellites, bool ring)
  {
    this->name = name;
    this->mass = mass;
    this->volume = volume;
    this->radius = radius;
    this->density = density;
    this->velocity = velocity;
    this->orbit = orbit;
    this->gravity = gravity;
    this->perihelion = perihelion;
    this->aphelion = aphelion;
    this->satellites = satellites;
    this->ring = ring;
  }

  double getMass() const {
    return this->mass;
  }

  double getVolume() const {
    return this->volume;
  }

  double getRadius() const {
    return this->radius;
  }

  double getDensity() const {
    return this->density;
  }

  double getVelocity() const {
    return this->velocity;
  }

  double getOrbit() const {
    return this->orbit;
  }

  double getGravity() const {
    return this->gravity;
  }

  double getPerihelion() const {
    return this->perihelion;
  }

  double getAphelion() const {
    return this->aphelion;
  }

  int getSatellites() const {
    return this->satellites;
  }

  bool getRing() const {
    return this->ring;
  }

  void setMass(double mass) {
    this->mass = mass;
  }

  void setVolume(double volume) {
    this->volume = volume;
  }

  void setRadius(double radius) {
    this->radius = radius;
  }

  void setDensity(double density) {
    this->density = density;
  }

  void setVelocity(double velocity) {
    this->velocity = velocity;
  }

  void setOrbit(double orbit) {
    this->orbit = orbit;
  }

  void setGravity(double gravity) {
    this->gravity = gravity;
  }

  void setPerihelion(double perihelion) {
    this->perihelion = perihelion;
  }

  void setAphelion(double aphelion) {
    this->aphelion = aphelion;
  }

  void setSatellites(int satellites) {
    this->satellites = satellites;
  }

  void setRing(bool ring) {
    this->ring = ring;
  }

  ~CelestialBody() { };
};

#endif // CELESTIALBODY_H
