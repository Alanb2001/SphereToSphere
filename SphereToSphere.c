#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

typedef struct {
    Vector3 position;
    float radius;
    Color sphereColour;  
    Vector3 velocity;
    float mass;
}Sphere;

   const int numSpheres = 2;

bool SphereDetection(Sphere sphere1, Sphere sphere2)
{      
    Vector3 p1 = sphere1.position;
    Vector3 p2 = sphere2.position;
    float r1 = sphere1.radius;
    float r2 = sphere2.radius;
    Vector3 v1 = sphere1.velocity;
    Vector3 v2 = sphere2.velocity;
    float a = Vector3LengthSqr(Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime()));
    float b = Vector3DotProduct(Vector3Subtract(p1, p2), Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime() * 2));
    float c = (Vector3LengthSqr(Vector3Scale(Vector3Subtract(p1, p2), (r1 + r2) * (r1 + r2))));
    float t = (-b - (b * b - 4 * a * c)) / (2 * a);

    if (t < 1 && t > 0)
    {
        printf("%f\nHit\n",t);
        return true;
    }
    
    return false;
}

void SphereResponse(Sphere *sphere1, Sphere *sphere2)
{
    Vector3 v1 = sphere1->velocity;
    float c = sphere2->radius / 2;
    Vector3 s = Vector3Add(sphere1->position, sphere2->position);
    Vector3 g = Vector3Subtract(sphere2->velocity, s);
    Vector3 q = Vector3Angle(v1, g);
    Vector3 co = cosf(q, g / v1);
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "SphereToSphere");

    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    
    Sphere spheres[numSpheres];
    spheres[0].position = (Vector3){5.0f, 0.0f, 0.0f};
    spheres[0].radius = (float){1.5f};
    spheres[0].sphereColour = GREEN;
    spheres[0].velocity = (Vector3){-1.0f, 0.0f, 0.0f};
    spheres[0].mass = (float){1.0f};
    
    spheres[1].position = (Vector3){-5.0f, 0.0f, 0.0f};
    spheres[1].radius = (float){1.5f};
    spheres[1].sphereColour = RED;
    spheres[1].velocity = (Vector3){1.0f, 0.0f, 0.0f};
    spheres[1].mass = (float){1.0f};

    
    while (!WindowShouldClose())
    {
        SphereDetection(spheres[0], spheres[1]);  
        
        SphereResponse(&spheres[0], &spheres[1]);
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
                
            BeginMode3D(camera);                

            for(int i = 0; i < numSpheres; i++)
            {
                DrawSphere(spheres[i].position, spheres[i].radius, spheres[i].sphereColour);
                DrawSphereWires(spheres[i].position, spheres[i].radius, 16, 16, BLACK);
                spheres[i].position = Vector3Add(spheres[i].position, Vector3Scale(spheres[i].velocity, GetFrameTime()));
            }
                         
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}