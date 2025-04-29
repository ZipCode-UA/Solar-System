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

  // Seed random number generator
  SetRandomSeed(time(nullptr));

  // Initialize random rotation angles
  for (int i = 0; i != SolarSystem.size(); ++i)
  {
    if (SolarSystem[i].getName() != "Sun")
    {
      SolarSystem[i].setOrbitPosition(GetRandomValue(0, 360));
      SolarSystem[i].setAxisPosition(GetRandomValue(0, 360));
    }
  }

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
  
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    handleMouseClick(window->getCamera(), models, SolarSystem);

  if (!pause)
  {
    elapsedTime += timeScale;

    const double secondsInDay = 86400;
    days = elapsedTime / secondsInDay;

    for (int i = 0; i != SolarSystem.size(); ++i)
    {
      SolarSystem[i].updateOrbitPosition(PI, timeScale);
      // TODO: Move rotation check to draw function
      if (rotation)
        SolarSystem[i].updateAxisPosition(PI, timeScale);
    }
  }

  if (window->Open())
    window->Draw(font, background, models, SolarSystem, days, timeScale, displayInput);
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
