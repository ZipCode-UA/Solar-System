#include "Simulation.h"

#include <memory>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include <raylib.h>

#include "CelestialBody.h"
#include "Input.h"
#include "SolarSystem.h"
#include "Window.h"

Simulation::Simulation()
{
  // Create Window
  window = std::make_unique<Window>();

  // Load default Solar System
  SolarSystem = getSolarSystem();
  Celestial::sort(SolarSystem);
  Celestial::setBounds(SolarSystem);

  // Load resources
  LoadResourceDirectory(resourceDirectory);
  LoadFont(fontDirectory);
  LoadTextures(textureDirectory);
  LoadModels();

  // Initialize rotation angles
  for (const auto iter : SolarSystem)
  {
    orbitRotationAngles.push_back(0);
    axisRotationAngles.push_back(0);
  }

  // Seed random number generator
  SetRandomSeed(time(nullptr));
  
  // Toggle running state
  running = true;
}

Simulation::~Simulation()
{
  UnloadFont(font);

  for (const auto iter : textures)
    UnloadTexture(iter);

  for (const auto iter : models)
    UnloadModel(iter);

  UnloadTexture(background);
}

void Simulation::update()
{
  handleInput();

  if (!pause)
  {
    elapsedTime += timeScale;
    updateRotation();
  }

  if (window->Open())
    window->Draw(font, background, models, SolarSystem, orbitRotationAngles, axisRotationAngles, days, timeScale);
  else
    running = false;
}

void Simulation::LoadResourceDirectory(const std::string& directory)
{
  // Check the working directory
  if (DirectoryExists(directory.c_str()))
  {
    ChangeDirectory(TextFormat("%s/%s", GetWorkingDirectory(), directory.c_str()));
    return;
  }

  // Check application directory and 3 directories back
  std::string text = "%s%s";
  const std::string applicationDirectory = GetApplicationDirectory();
  for (int i = 0; i != 4; ++i)
  {
    const std::string dir = TextFormat(text.c_str(), applicationDirectory.c_str(), directory.c_str());
    if (DirectoryExists(dir.c_str()))
    {
      ChangeDirectory(dir.c_str());
      return;
    }
    text.insert(2, "../");
  }

  std::cerr << "Could not find resource directory";
  exit(1);
}

void Simulation::LoadFont(const std::string& directory)
{
  font = LoadFontEx("SpaceMono/SpaceMonoNerdFontMono-Bold.ttf", 64, 0, 0);
}

void Simulation::LoadTextures(const std::string& directory)
{
  // Load background texture
  const std::string backgroundPath = directory + "Stars.jpg";
  background = LoadTexture(backgroundPath.c_str()); // Load image data into GPU memory (VRAM)

  // Load CelestialBody textures
  for (const auto iter : SolarSystem)
  {
    const std::string celestialBodyPath = directory + iter.getFileName();
    Texture2D texture = LoadTexture(celestialBodyPath.c_str());
    textures.push_back(texture);
  }
}

void Simulation::LoadModels()
{
  // Load CelestialBody models
  int i = 0;
  for (const auto iter : SolarSystem)
  {
    Mesh mesh = GenMeshSphere(1.0f, 32, 32);
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures[i++];
    models.push_back(model);
  }
}

void Simulation::updateRotation()
{
  // Update rotation vectors
  const double secondsInDay = 86400;
  const double secondsInHour = 3600;
  days = elapsedTime / secondsInDay;
  int i = 0;
  for (const auto iter : SolarSystem)
  {
    // Skip the sun
    if (iter.getOrbit() == 0 || iter.getOrbitRadius() == 0)
    {
      ++i;
      continue;
    }

    // Calculate orbit angle displacement per second
    const double orbitSeconds = iter.getOrbit() * secondsInDay;
    const double orbitAngularVelocity = (2 * PI) / orbitSeconds;
    const double orbitDisplacement = orbitAngularVelocity * (180 / PI);
    orbitRotationAngles[i] += orbitDisplacement * static_cast<double>(timeScale);

    // Calculate axis angle displacement per second
    if (rotation)
    {
      const double axisSeconds = iter.getAxisRotation() * secondsInHour;
      const double axisAngularVelocity = (2 * PI) / axisSeconds;
      const double axisDisplacement = axisAngularVelocity * (180 / PI);
      axisRotationAngles[i] += axisDisplacement * static_cast<double>(timeScale);
    }

    ++i;
  }
}
