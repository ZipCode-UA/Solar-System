#ifndef SIMULATION_H
#define SIMULATION_H

#include <memory>
#include <string>
#include <vector>

#include <raylib.h>

#include "CelestialBody.h"
#include "Window.h"

class Simulation
{
public:
  Simulation();
  ~Simulation();

public:
  void update();

private:
  void LoadResourceDirectory(const std::string& directory);
  void LoadFont(const std::string& directory);
  void LoadTextures(const std::string& directory);
  void LoadModels();

private:
  void updateRotation();

private:
  static const int timeScaleDefault = 20000;

public:
  static inline int timeScale = timeScaleDefault;
  static inline int timeScaleModifier = 1000;
  static inline int bigTimeScaleModifier = timeScaleModifier * 10;
  static inline bool rotation = false;
  static inline bool pause = false;

private:
  double elapsedTime = 0;
  int days = 0;

private:
  std::unique_ptr<Window> window;
  Font font;
  Texture2D background;
  std::vector<Texture2D> textures;
  std::vector<Model> models;

private:
  std::vector<CelestialBody> SolarSystem;
  std::vector<double> orbitRotationAngles;
  std::vector<double> axisRotationAngles;

private:
  const std::string resourceDirectory = "resources";
  const std::string textureDirectory = "assets/textures/";
  const std::string fontDirectory = "assets/fonts/";

public:
  bool running = false;
};

#endif // SIMULATION_H
