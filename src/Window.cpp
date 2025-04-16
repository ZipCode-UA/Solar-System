/*******************************************************************************************
*
*   code from https://www.raylib.com/examples/models/loader.html?name=models_rlgl_solar_system
*
*   raylib [models] example - rlgl module usage with push/pop matrix transformations
*
*   Example complexity rating: [★★★★] 4/4
*
*   NOTE: This example uses [rlgl] module functionality (pseudo-OpenGL 1.1 style coding)
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Window.h"

#include <vector>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "CelestialBody.h"

Window::Window(const std::vector<CelestialBody>& SolarSystem)
  : SolarSystem(SolarSystem),
    focalSize(static_cast<float>(SolarSystem.crbegin()->getOrbitRadius() * focalScale))
{
  InitWindow(1600, 1000, "Solar System");
  ToggleBorderlessWindowed();
  InitCamera();
  SetTargetFPS(60);
  LoadTextures();
  LoadModels();

  for (const auto iter : SolarSystem)
  {
    orbitRotationAngles.push_back(0);
    axisRotationAngles.push_back(0);
  }
}

Window::~Window()
{
  UnloadTexture(background);
  
  for (const auto iter : textures)
    UnloadTexture(iter);

  for (const auto iter : models)
    UnloadModel(iter);

  CloseWindow();
}

void Window::InitCamera()
{
  camera.position = Vector3{ focalSize, focalSize, focalSize }; // Camera position
  camera.target = Vector3{ 0.0f, 0.0f, 0.0f }; // Camera looking at point
  camera.up = Vector3{ 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f; // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  // Override the projection matrix with a custom far clipping plane to ensure far objects are rendered
  proj = MatrixPerspective(camera.fovy * DEG2RAD,
    (float)GetScreenWidth() / (float)GetScreenHeight(),
    nearPlane, farPlane);
}

void Window::LoadTextures()
{
  // TODO: Link assets directory to CMake build directory for shorter paths :)
  background = LoadTexture("../assets/textures/Stars.jpg"); // Load image data into GPU memory (VRAM)

  for (const auto iter : SolarSystem)
  {
    std::string path = "../assets/textures/";
    std::string name = iter.getFileName();
    path += name;
    Texture2D texture = LoadTexture(path.c_str());
    textures.push_back(texture);
  }
}

void Window::LoadModels()
{
  int i = 0;
  for (const auto iter : SolarSystem)
  {
    Mesh mesh = GenMeshSphere(1.0f, 32, 32);
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures[i++];
    models.push_back(model);
  }
}

void Window::DrawBackground()
{
  DrawTexture(background, 0, 0, WHITE);
}

void Window::DrawCelestialBodies()
{
  int i = 0;
  for (const auto iter : SolarSystem)
  {
    const float scaledOrbitRadius = static_cast<float>(iter.getOrbitRadius());
    const float scaledRadius = static_cast<float>(iter.getRadius());

    rlPushMatrix();
      rlRotatef(orbitRotationAngles[i], 0.0f, 1.0f, 0.0f); // Rotation of CelestialBody orbit around the Sun
      rlTranslatef(scaledOrbitRadius, 0.0f, 0.0f); // Translation of CelestialBody orbit
      rlPushMatrix();
        rlRotatef(axisRotationAngles[i], 0.25f, 1.0f, 0.0f); // Rotation of CelestialBody itself
        rlScalef(scaledRadius, scaledRadius, scaledRadius); // Scale CelestialBody
        DrawModel(models[i], (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE); // Draw the CelestialBody
      rlPopMatrix();
    rlPopMatrix();
    ++i;
  }
}

bool Window::Open()
{
  return !WindowShouldClose();
}

void Window::Update(float& elapsedTime)
{
  elapsedTime += GetFrameTime();

  UpdateCamera(&camera, CAMERA_ORBITAL);

  /*
  // Update rotation vectors
  int i = 0;
  const double secondsInDay = 86400;
  const double daysElapsed = (elapsedTime * timeScale) / secondsInDay;
  for (const auto iter : SolarSystem)
  {
    const double daysPerOneOrbitDegree = iter.getOrbit() / 360.0f;
    orbitRotationAngles[i] = daysElapsed / daysPerOneOrbitDegree;

    const double daysPerOneAxisDegree = iter.getAxisRotation() / 360.0f;
    axisRotationAngles[i] = daysElapsed / daysPerOneAxisDegree;

    ++i;
  }
  */

  // Update rotation vectors
  int i = 0;
  for (const auto iter : SolarSystem)
  {
    orbitRotationAngles[i] = (iter.getOrbit() / 360.0f) * timeScale;
    axisRotationAngles[i] = (iter.getAxisRotation() / 360.0f) * timeScale;
    ++i;
  }

  BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();
    BeginMode3D(camera);
      rlSetMatrixProjection(proj); // Override the projection matrix with a custom far plane
      DrawCelestialBodies();
    EndMode3D();
  EndDrawing();
}
