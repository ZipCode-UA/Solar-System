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
  void LoadTextures();
  void LoadModels();
  void DrawBackground();
  void DrawCelestialBodies();

public:
  bool Open();
  void Update(float& elapsedTime);

private:
  Camera camera = { 0 };
  Matrix proj;
  Texture2D background;

private:
  const std::vector<CelestialBody>& SolarSystem;
  std::vector<double> orbitRotationAngles;
  std::vector<double> axisRotationAngles;
  std::vector<Texture2D> textures;
  std::vector<Model> models;

private:
  const float nearPlane = 1.0f;
  const float farPlane = 100000.0f;
  const float focalScale = 1.0f;
  const float focalSize;
  const float timeScale = 1.0f;
};

#endif // WINDOW_H
