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

#include <cmath>
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

  for (const auto iter : SolarSystem)
    rotation.push_back(0);
}

Window::~Window()
{
  UnloadTexture(background);
  CloseWindow();
}

void Window::SetMatrixProjection()
{
  rlMatrixMode(RL_PROJECTION);
  rlLoadIdentity();
  rlMultMatrixf(MatrixToFloat(proj));
  rlMatrixMode(RL_MODELVIEW);
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
  //SetMatrixProjection();
}

void Window::LoadBackground()
{
  // TODO: Link assets directory to CMake build directory for shorter paths :)
  background = LoadTexture("../assets/textures/Stars.jpg"); // Load image data into GPU memory (VRAM)
  sun = LoadTexture("../assets/textures/Sun.jpg"); // Load image data into GPU memory (VRAM)
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
      rlRotatef(0.0f, 0.0f, 1.0f, 0.0f); // Rotation of CelestialBody orbit
      rlTranslatef(scaledOrbitRadius, 0.0f, 0.0f); // Translation of CelestialBody orbit
      rlPushMatrix();
        rlRotatef(rotation[i], 0.25f, 1.0f, 0.0f); // Rotation of CelestialBody
        rlScalef(scaledRadius, scaledRadius, scaledRadius); // Scale CelestialBody
        DrawSphere((Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, YELLOW); // Draw a sphere
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

  // TODO: Create parallel vector of rotation data and calculate rotation

  BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();
    BeginMode3D(camera);
      rlSetMatrixProjection(proj); // Override the projection matrix with a custom far plane
      DrawCelestialBodies();
    EndMode3D();
  EndDrawing();
}
