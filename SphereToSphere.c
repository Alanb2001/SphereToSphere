/*******************************************************************************************
*
*   raylib [models] example - Detect basic 3d collisions (box vs sphere vs box)
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

typedef struct {
    Vector3 position;
    float radius;
    Color sphereColour;  
    Vector3 velocity;
    float mass;
}Sphere;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int numSpheres = 2;
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - box collisions");

    // Define the camera to look into our 3d world
    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    
    Sphere spheres[numSpheres];
    spheres[0].position = (Vector3){0.0f, 1.0f, 2.0f};
    spheres[0].radius = (float){1.5f};
    spheres[0].sphereColour = GREEN;
    
    spheres[1].position = (Vector3){0.0f, 1.0f, 5.0f};
    spheres[1].radius = (float){1.5f};
    spheres[1].sphereColour = RED;

    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update here
        BeginDrawing();

            ClearBackground(RAYWHITE);
                
            BeginMode3D(camera);
            
            // Draw here
            for(int i = 0; i < numSpheres; i++)
            {
               DrawSphere(spheres[i].position, spheres[i].radius, spheres[i].sphereColour);
               DrawSphereWires(spheres[i].position, spheres[i].radius, 16, 16, BLACK);
            }
            
            
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}