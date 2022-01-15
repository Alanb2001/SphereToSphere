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

    const int numSpheres = 4;

void SphereToSphereTest(Sphere *sphere1, Sphere *sphere2, float delta)
{
    Vector3 dp = Vector3Subtract(sphere2->position, sphere1->position);
    Vector3 dv = Vector3Scale(Vector3Subtract(sphere2->velocity, sphere1->velocity), delta);
    float r1r2 = sphere1->radius + sphere2->radius;
    
    float a2 = Vector3LengthSqr(dv) * 2.0;
    float b = 2.0 * Vector3DotProduct(dp, dv);
    float c = Vector3LengthSqr(dp) - pow(r1r2, 2.0);
    
    float disc = sqrt(pow(b, 2.0) - 2 * a2 * c);
    
    float t1 = (-b - disc) / a2;
    float t2 = (-b + disc) / a2;
    
    bool areColliding = t1 < 1 && t1 > 0;
    bool areInside = t1 < 0 && t2 > 1;
    if (!areColliding && !areInside)
    {
        return;
    }
    
    sphere1->position = Vector3Add(sphere1->position, Vector3Scale(sphere1->velocity, delta * t1));
    sphere2->position = Vector3Add(sphere2->position, Vector3Scale(sphere2->velocity, delta * t1));
    Vector3 v1 = sphere1->velocity;
    Vector3 g = Vector3Normalize(Vector3Subtract(sphere2->position, sphere1->position));
    float q = Vector3DotProduct(v1, g) * (Vector3Length(v1) / sphere2->mass);
    sphere2->velocity = Vector3Add(sphere2->velocity, Vector3Scale(g, q));
    
    sphere1->velocity = (Vector3)
    {
        (sphere1->velocity.x * sphere1->mass - sphere2->velocity.x * sphere2->mass) / sphere1->mass,
        (sphere1->velocity.y * sphere1->mass - sphere2->velocity.y * sphere2->mass) / sphere1->mass,
        (sphere1->velocity.z * sphere1->mass - sphere2->velocity.z * sphere2->mass) / sphere1->mass
    };
}

bool SphereDetection(Sphere *sphere1, Sphere *sphere2)
{   
    Vector3 p1 = sphere1->position;
    Vector3 p2 = sphere2->position;
    float r1 = sphere1->radius;
    float r2 = sphere2->radius;
    Vector3 v1 = sphere1->velocity;
    Vector3 v2 = sphere2->velocity;
    float a = Vector3LengthSqr(Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime()));
    float b = Vector3DotProduct(Vector3Subtract(p1, p2), Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime() * 2));
    float c = (Vector3LengthSqr(Vector3Scale(Vector3Subtract(p1, p2), (r1 + r2) * (r1 + r2))));
    float t = (-b - (b * b - 4 * a * c)) / (2 * a);
        
    if (t < 1 && t > 0)
    {
        printf("%f\nHit\n",t);
        //Vector3 v1 = sphere1->velocity;
        //Vector3 g = Vector3Normalize(Vector3Subtract(sphere2->position, sphere1->position));
        //float q = Vector3DotProduct(v1, g) * (Vector3Length(v1) / sphere2->mass);
        //sphere2->velocity = Vector3Add(sphere2->velocity, Vector3Scale(g, q));
        return true;
    }

    return false;
}

void SphereResponse(Sphere *sphere1, Sphere *sphere2)
{   
   sphere1->position = Vector3Add(sphere1->position, Vector3Scale(sphere1->velocity, GetFrameTime()));
   sphere2->position = Vector3Add(sphere2->position, Vector3Scale(sphere2->velocity, GetFrameTime()));
   Vector3 v1 = sphere1->velocity;
   //float c = sphere2->radius / 2;
   //Vector3 s = Vector3Add(sphere1->position, sphere2->position);
   //Vector3 p = Vector3AddValue(s, c);
   Vector3 g = Vector3Normalize(Vector3Subtract(sphere2->position, sphere1->position));
   float q = Vector3DotProduct(v1, g) * (Vector3Length(v1) / sphere2->mass);
   sphere2->velocity = Vector3Add(sphere2->velocity, Vector3Scale(g, q));
   //float co = cos(c) / (sphere1->radius + sphere2->radius);
   sphere1->velocity = (Vector3) { 
   (sphere1->velocity.x * sphere1->mass - sphere2->velocity.x * sphere2->mass) / sphere1->mass,
   (sphere1->velocity.y * sphere1->mass - sphere2->velocity.y * sphere2->mass) / sphere1->mass,
   (sphere1->velocity.z * sphere1->mass - sphere2->velocity.z * sphere2->mass) / sphere1->mass
   };
   printf("\nResponse\n");
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

    spheres[2].position = (Vector3){5.0f, 5.0f, 0.0f};
    spheres[2].radius = (float){1.5f};
    spheres[2].sphereColour = YELLOW;
    spheres[2].velocity = (Vector3){-1.0f, 0.0f, 0.0f};
    spheres[2].mass = (float){1.0f};
    
    spheres[3].position = (Vector3){-5.0f, 5.0f, 0.0f};
    spheres[3].radius = (float){1.5f};
    spheres[3].sphereColour = PINK;
    spheres[3].velocity = (Vector3){1.0f, 0.0f, 0.0f};
    spheres[3].mass = (float){1.0f};
    
    while (!WindowShouldClose())
    {
        for (int i = 0; i < numSpheres; i++)
        {
            for (int j = 0; j < numSpheres; j++)
            {
                //if (SphereDetection(&spheres[i], &spheres[j]) == true)
                //{
                //    SphereResponse(&spheres[i], &spheres[j]);
                //}
                SphereToSphereTest(&spheres[i], &spheres[j], 1.0);
            }
        }
        
        //SphereDetection(&spheres[0], &spheres[1]);
        //SphereDetection(&spheres[2], &spheres[3]);
        //SphereToSphereTest(&spheres[0], &spheres[1], 1.0);
        //SphereToSphereTest(&spheres[2], &spheres[3], 1.0);

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