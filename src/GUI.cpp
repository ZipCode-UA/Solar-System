#include "raylib.h"
#include <math.h>   // Required for: cosf(), sinf()

#define DEG2RAD (0.01745329251994329577f)

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Radii for solar system bodies
    const float sunRadius         = 4.0f;
    const float earthRadius       = 0.6f;
    const float earthOrbitRadius  = 8.0f;
    const float moonRadius        = 0.16f;
    const float moonOrbitRadius   = 1.5f;

    // Additional test sphere parameters
    const float orbitRadius = 5.0f;
    const float orbitSpeed  = 1.0f;

    InitWindow(screenWidth, screenHeight, "Solar System Model - Models API");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 16.0f, 16.0f, 16.0f };
    camera.target   = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Rotation variables (angles in degrees)
    float rotationSpeed     = 0.2f;
    float earthRotation     = 0.0f;   // Earth's self rotation
    float earthOrbitRotation= 0.0f;   // Earth's orbit around Sun
    float moonRotation      = 0.0f;   // Moon's self rotation
    float moonOrbitRotation = 0.0f;   // Moon's orbit around Earth

    // Create a sphere mesh and load it as a model (used for all bodies)
    Model sphereModel = LoadModelFromMesh(GenMeshSphere(1.0f, 16, 16));

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_CUSTOM);

        // Increment rotations
        earthRotation      += 5.0f  * rotationSpeed;
        earthOrbitRotation += (365.0f/360.0f * 5.0f * rotationSpeed * rotationSpeed);
        moonRotation       += 2.0f  * rotationSpeed;
        moonOrbitRotation  += 8.0f  * rotationSpeed;

        // Compute Earth's position in its orbit around the Sun
        Vector3 earthPos = {
            earthOrbitRadius * cosf(DEG2RAD * earthOrbitRotation),
            0.0f,
            earthOrbitRadius * sinf(DEG2RAD * earthOrbitRotation)
        };

        // Compute Moon's position relative to Earth
        Vector3 moonOffset = {
            moonOrbitRadius * cosf(DEG2RAD * moonOrbitRotation),
            0.0f,
            moonOrbitRadius * sinf(DEG2RAD * moonOrbitRotation)
        };
        Vector3 moonPos = {
            earthPos.x + moonOffset.x,
            earthPos.y + moonOffset.y,
            earthPos.z + moonOffset.z
        };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw the Sun at the center (gold)
                DrawModelEx(sphereModel, (Vector3){ 0, 0, 0 }, (Vector3){ 0, 1, 0 }, 0.0f, 
                            (Vector3){ sunRadius, sunRadius, sunRadius }, GOLD);

                // Draw the Earth (blue) at its orbit position and rotated about an arbitrary axis
                DrawModelEx(sphereModel, earthPos, (Vector3){ 0.25f, 1.0f, 0.0f }, earthRotation, 
                            (Vector3){ earthRadius, earthRadius, earthRadius }, BLUE);

                // Draw the Moon (light gray) at its computed position and with its own rotation
                DrawModelEx(sphereModel, moonPos, (Vector3){ 0, 1, 0 }, moonRotation, 
                            (Vector3){ moonRadius, moonRadius, moonRadius }, LIGHTGRAY);

                // Draw reference elements
                DrawCircle3D((Vector3){ 0, 0, 0 }, earthOrbitRadius, (Vector3){ 1, 0, 0 }, 90.0f, Fade(RED, 0.5f));
                DrawGrid(20, 1.0f);

            EndMode3D();

            DrawText("EARTH ORBITING AROUND THE SUN!", 400, 10, 20, MAROON);
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(sphereModel);  // Unload sphere model
    CloseWindow();             // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}