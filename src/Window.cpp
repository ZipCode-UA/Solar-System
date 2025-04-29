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
#include "UI.h"

Window::Window()
{
  // Setup Window
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Solar System");
  ToggleBorderlessWindowed();
  HideCursor();

  // Setup Internals
  InitCamera();
  SetTargetFPS(60);
}

Window::~Window()
{
  CloseWindow();
}

void Window::InitCamera()
{
  camera.position = Vector3{ 0, 0, 0 }; // Camera position
  camera.target = Vector3{ 0.0f, 0.0f, 0.0f }; // Camera looking at point
  camera.up = Vector3{ 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f; // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  // Override the projection matrix with a custom far clipping plane to ensure far objects are rendered
  proj = MatrixPerspective(camera.fovy * DEG2RAD,
    (float)GetScreenWidth() / (float)GetScreenHeight(),
    nearPlane, farPlane);
}

void Window::DrawBackground(Texture2D& background)
{
  DrawTexture(background, 0, 0, WHITE);
}

void Window::DrawCelestialBodies(std::vector<Model>& models,
                                 std::vector<CelestialBody>& SolarSystem)
{
  int i = 0;
  for (const auto iter : SolarSystem)
  {
    const float scaledOrbitRadius = static_cast<float>(iter.getOrbitRadius());
    const float scaledRadius = static_cast<float>(iter.getRadius());

    rlPushMatrix();
      rlRotatef(static_cast<float>(iter.getOrbitPosition()), 0.0f, 1.0f, 0.0f); // Rotation of CelestialBody orbit around the Sun
      rlTranslatef(scaledOrbitRadius, 0.0f, 0.0f); // Translation of CelestialBody orbit
      rlPushMatrix();
        rlRotatef(static_cast<float>(iter.getAxisPosition()), 0.25f, 1.0f, 0.0f); // Rotation of CelestialBody itself
        rlScalef(scaledRadius, scaledRadius, scaledRadius); // Scale CelestialBody
        DrawModel(models[i], { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE); // Draw the CelestialBody
      rlPopMatrix();
    rlPopMatrix();
    ++i;
  }
}

bool Window::Open()
{
  return !WindowShouldClose();
}

void Window::Draw(Font& font,
                  Texture2D& background,
                  std::vector<Model>& models,
                  std::vector<CelestialBody>& SolarSystem,
                  int days,
                  int timeScale,
                  bool displayInput)
{
  const float focalSize = (static_cast<float>(SolarSystem.crbegin()->getOrbitRadius() * focalScale));
  camera.position = Vector3{ focalSize, focalSize, focalSize }; // Camera position

  UpdateCamera(&camera, CAMERA_ORBITAL);

  BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground(background);
    DrawUI(font, SolarSystem, days, timeScale, displayInput);
    BeginMode3D(camera);
      rlSetMatrixProjection(proj); // Override the projection matrix with a custom far plane
      DrawCelestialBodies(models, SolarSystem);
    EndMode3D();
  EndDrawing();
}
