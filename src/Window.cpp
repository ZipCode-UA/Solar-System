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

#include "raylib.h"
#include "rlgl.h"

// TODO: Use actual values
const float sunRadius = 4.0f;
const float earthRadius = 0.6f;
const float earthOrbitRadius = 8.0f;
const float moonRadius = 0.16f;
const float moonOrbitRadius = 1.5f;
float rotationSpeed = 0.2f;         // General system rotation speed
float earthRotation = 0.0f;         // Rotation of earth around itself (days) in degrees
float earthOrbitRotation = 0.0f;    // Rotation of earth around the Sun (years) in degrees
float moonRotation = 0.0f;          // Rotation of moon around itself
float moonOrbitRotation = 0.0f;     // Rotation of moon around earth in degrees

Window::Window()
{
  InitWindow(800, 800, "Solar System");
  InitCamera();
  SetTargetFPS(60);
}

Window::~Window()
{
  CloseWindow();
}

void Window::InitCamera()
{
  camera.position = (Vector3){ 16.0f, 16.0f, 16.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
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

  // TODO: Use actual values
  earthRotation += (5.0f*rotationSpeed);
  earthOrbitRotation += (365/360.0f*(5.0f*rotationSpeed)*rotationSpeed);
  moonRotation += (2.0f*rotationSpeed);
  moonOrbitRotation += (8.0f*rotationSpeed);

  BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera);

        rlPushMatrix();
            rlScalef(sunRadius, sunRadius, sunRadius);          // Scale Sun
            DrawSphereBasic(GOLD);                              // Draw the Sun
        rlPopMatrix();

        rlPushMatrix();
            rlRotatef(earthOrbitRotation, 0.0f, 1.0f, 0.0f);    // Rotation for Earth orbit around Sun
            rlTranslatef(earthOrbitRadius, 0.0f, 0.0f);         // Translation for Earth orbit

            rlPushMatrix();
                rlRotatef(earthRotation, 0.25, 1.0, 0.0);       // Rotation for Earth itself
                rlScalef(earthRadius, earthRadius, earthRadius);// Scale Earth

                DrawSphereBasic(BLUE);                          // Draw the Earth
            rlPopMatrix();

            rlRotatef(moonOrbitRotation, 0.0f, 1.0f, 0.0f);     // Rotation for Moon orbit around Earth
            rlTranslatef(moonOrbitRadius, 0.0f, 0.0f);          // Translation for Moon orbit
            rlRotatef(moonRotation, 0.0f, 1.0f, 0.0f);          // Rotation for Moon itself
            rlScalef(moonRadius, moonRadius, moonRadius);       // Scale Moon

            DrawSphereBasic(LIGHTGRAY);                         // Draw the Moon
        rlPopMatrix();

        // Some reference elements (not affected by previous matrix transformations)
        DrawCircle3D((Vector3){ 0.0f, 0.0f, 0.0f }, earthOrbitRadius, (Vector3){ 1, 0, 0 }, 90.0f, Fade(RED, 0.5f));
        DrawGrid(20, 1.0f);

    EndMode3D();

    DrawText("EARTH ORBITING AROUND THE SUN!", 400, 10, 20, MAROON);
    DrawFPS(10, 10);

  EndDrawing();
}

bool Window::Open()
{
  return !WindowShouldClose();
}
