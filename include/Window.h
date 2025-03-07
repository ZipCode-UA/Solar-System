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
  void SetMatrixProjection();
  void InitCamera();
  void LoadBackground();
  void DrawBackground();
  void DrawCelestialBody(Color color); // Draw sphere without any matrix transformation
  void DrawCelestialBodies();

public:
  bool Open();
  void Update();

private:
  Camera camera = { 0 };
  Matrix proj;
  Texture2D background;

private:
  const std::vector<CelestialBody>& SolarSystem;
  std::vector<float> rotation;

private:
  const float nearPlane = 1.0f;
  const float farPlane = 100000.0f;
  const float focalScale = 1.0f;
  const float focalSize;
};

#endif // WINDOW_H
