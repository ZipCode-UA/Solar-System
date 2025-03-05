#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include "raylib.h"

#include "CelestialBody.h"

class Window
{
public:
  Window(const std::vector<CelestialBody>& SolarSystem);
  ~Window();

private:
  void InitCamera();
  void DrawSphereBasic(Color color); // Draw sphere without any matrix transformation

public:
  bool Open();
  void Update();

private:
  Camera camera = { 0 };

private:
  const std::vector<CelestialBody>& SolarSystem;
  std::vector<float> rotation;

private:
  const float focalScale = 1;
  const float focalSize;
};

#endif // WINDOW_H
