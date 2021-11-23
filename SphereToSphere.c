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

bool SphereDetection()
{    
    Vector3 p1 = spheres[0].position;
    Vector3 p2 = spheres[1].position;
    float r1 = spheres[0].radius;
    float r2 = spheres[1].radius;
    Vector3 v1 = spheres[0].velocity;
    Vector3 v2 = spheres[1].velocity;
    float a = Vector3LengthSqr(Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime()));
    float b = Vector3DotProduct(Vector3Subtract(p1, p2), Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime() * 2));
    float c = (Vector3LengthSqr(Vector3Scale(Vector3Subtract(p1, p2), (r1 + r2) * (r1 + r2))));
    float t = (-b - (b * b - 4 * a * c)) / (2 * a);

    if (t < 1 && t > 0)
    {
        printf("%f\nHit\n");
        return true;
    }
    
    return false;
}

int main(void)
{
    const int numSpheres = 2;
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "SphereToSphere");

    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    
    Sphere spheres[numSpheres];
    spheres[0].position = (Vector3){0.0f, 1.0f, 2.0f};
    spheres[0].radius = (float){1.5f};
    spheres[0].sphereColour = GREEN;
    spheres[0].velocity = (Vector3){1.0f, 0.0f, 0.0f};
    spheres[0].mass = (float){1.0f};
    
    spheres[1].position = (Vector3){0.0f, 1.0f, 5.0f};
    spheres[1].radius = (float){1.5f};
    spheres[1].sphereColour = RED;
    spheres[1].velocity = (Vector3){-1.0f, 0.0f, 0.0f};
    spheres[1].mass = (float){1.0f};

    //Unity code
    //Vector3 p1 = spheres[j].transform.position;
    //Vector3 p2 = spheres[i].transform.position;
    //float r1 = spheres[j].GetComponent<MeshRenderer>().bounds.extents.magnitude;
    //float r2 = spheres[i].GetComponent<MeshRenderer>().bounds.extents.magnitude;
    //Vector3 v1 = spheres[j].GetComponent<StartingVelocity>().velocity;
    //Vector3 v2 = spheres[i].GetComponent<StartingVelocity>().velocity;
    //float a = ((v1 - v2) * Time.deltaTime).sqrMagnitude;
    //float b = Vector3.Dot(p1 - p2, (v1 - v2) * Time.deltaTime) * 2;
    //float c = (p1 - p2).sqrMagnitude - (r1 + r2) * (r1 + r2);
    //float t = (-b - Mathf.Sqrt(b * b - 4 * a * c)) / (2 * a);
    //
    //if (t < 1 && t > 0)
    //{
    //    print(t);
    //    print("Hit");
    //    return true;
    //}

    //transform.position += velocity * Time.deltaTime;

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
                
            BeginMode3D(camera);          
            
            for(int i = 0; i < numSpheres; i++)
            {
               DrawSphere(spheres[i].position, spheres[i].radius, spheres[i].sphereColour);
               DrawSphereWires(spheres[i].position, spheres[i].radius, 16, 16, BLACK);
               SphereDetection();               
            }
            
            
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}