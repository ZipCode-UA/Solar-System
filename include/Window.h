#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include "raylib.h"

#include "CelestialBody.h"

class Window
{
public:
  Window();
  ~Window();

private:
  void SetMatrixProjection();
  void InitCamera();
  void DrawBackground(Texture2D& background);
  void DrawCelestialBodies(std::vector<Model>& models,
                           std::vector<CelestialBody>& SolarSystem,
                           std::vector<double>& orbitRotationAngles,
                           std::vector<double>& axisRotationAngles);

public:
  bool Open();
  void Draw(Font& font,
            Texture2D& background,
            std::vector<Model>& models,
            std::vector<CelestialBody>& SolarSystem,
            std::vector<double>& orbitRotationAngles,
            std::vector<double>& axisRotationAngles,
            int days);

private:
  Camera camera = { 0 };
  Matrix proj;

private:
  const float nearPlane = 1.0f;
  const float farPlane = 100000.0f;
  float focalScale = 1.0f;
};

#endif // WINDOW_H
