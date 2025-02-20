#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

class CelestialBody
{ 
private: 
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
  CelestialBody(double mass, double volume, double radius, double density, double velocity, double orbit, double gravity, double perihelion, double aphelion, int satellites, bool ring)
  {
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

  void getMass(double mass) {
    this->mass = mass;
  }

  void getVolume(double volume) {
    this->volume = volume;
  }

  void getRadius(double radius) {
    this->radius = radius;
  }

  void getDensity(double density) {
    this->density = density;
  }

  void getVelocity(double velocity) {
    this->velocity = velocity;
  }

  void getOrbit(double orbit) {
    this->orbit = orbit;
  }

  void getGravity(double gravity) {
    this->gravity = gravity;
  }

  void getPerihelion(double perihelion) {
    this->perihelion = perihelion;
  }

  void getAphelion(double aphelion) {
    this->aphelion = aphelion;
  }

  void getSatellites(int satellites) {
    this->satellites = satellites;
  }

  void getRing(bool ring) {
    this->ring = ring;
  }

  ~CelestialBody() { };
};

#endif // CELESTIALBODY_H
