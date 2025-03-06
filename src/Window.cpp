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

#include "CelestialBody.h"

Window::Window(const std::vector<CelestialBody>& SolarSystem)
  : SolarSystem(SolarSystem),
    focalSize(static_cast<float>(SolarSystem.crbegin()->getOrbitRadius() * focalScale))
{
  InitWindow(1600, 1000, "Solar System");
  LoadStars();
  InitCamera();
  SetTargetFPS(60);

  for (const auto iter : SolarSystem)
    rotation.push_back(0);
}

Window::~Window()
{
  UnloadTexture(texture);
  CloseWindow();
}

void Window::InitCamera()
{
  camera.position = Vector3{ focalSize, focalSize, focalSize }; // Camera position
  camera.target = Vector3{ 0.0f, 0.0f, 0.0f }; // Camera looking at point
  camera.up = Vector3{ 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f; // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
}

void Window::LoadStars()
{
  // TODO: Link assets directory to CMake build directory for shorter paths :)
  image = LoadImage("../assets/textures/Stars.jpg"); // Load image data into CPU memory (RAM)
  texture = LoadTextureFromImage(image); // Image converted to texture, GPU memory (RAM -> VRAM)
  UnloadImage(image);  // Unload image data from CPU memory (RAM)

  image = LoadImageFromTexture(texture); // Load image from GPU texture (VRAM -> RAM)
  UnloadTexture(texture); // Unload texture from GPU memory (VRAM)

  texture = LoadTextureFromImage(image); // Recreate texture from retrieved image data (RAM -> VRAM)
  UnloadImage(image); // Unload retrieved image data from CPU memory (RAM)
}

void Window::DrawSphereBasic(Color color)
{
  int rings = 16;
  int slices = 16;

  // Make sure there is enough space in the internal render batch
  // buffer to store all required vertex, batch is reseted if required
  rlCheckRenderBatchLimit((rings + 2)*slices*6);

  rlBegin(RL_TRIANGLES);
      rlColor4ub(color.r, color.g, color.b, color.a);

      for (int i = 0; i < (rings + 2); i++)
      {
          for (int j = 0; j < slices; j++)
          {
              rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                         sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                         cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
              rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                         sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                         cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
              rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*(j*360/slices)),
                         sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                         cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*(j*360/slices)));

              rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                         sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                         cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
              rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*sinf(DEG2RAD*((j+1)*360/slices)),
                         sinf(DEG2RAD*(270+(180/(rings + 1))*(i))),
                         cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*cosf(DEG2RAD*((j+1)*360/slices)));
              rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                         sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                         cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
          }
      }
  rlEnd();
}

void Window::Update()
{
  UpdateCamera(&camera, CAMERA_ORBITAL);
  
  // TODO: Create parallel vector of rotation data and calculate rotation

  BeginDrawing();

    ClearBackground(BLACK);

    DrawTexture(texture, 0, 0, WHITE);

    BeginMode3D(camera);

      int i = 0;
      for (const auto iter : SolarSystem)
      {
        const float scaledOrbitRadius = static_cast<float>(iter.getOrbitRadius());
        const float scaledRadius = static_cast<float>(iter.getRadius());

        rlPushMatrix();

          rlRotatef(0.0f, 0.0f, 1.0f, 0.0f); // Rotation of CelestialBody orbit
          rlTranslatef(scaledOrbitRadius, 0.0f, 0.0f); // Translation of CelestialBody orbit

          rlPushMatrix();
            // TODO: Create parallel vector of rotation data and calculate rotation
            rlRotatef(rotation[i], 0.25f, 1.0f, 0.0f); // Rotation of CelestialBody
            rlScalef(scaledRadius, scaledRadius, scaledRadius); // Scale CelestialBody
            DrawSphereBasic(GOLD); // Color CelestialBody
          rlPopMatrix();

        rlPopMatrix();
        ++i;
      }

    EndMode3D();

  EndDrawing();
}

bool Window::Open()
{
  return !WindowShouldClose();
}
