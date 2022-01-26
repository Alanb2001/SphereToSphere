#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

typedef struct {
    Vector3 position;
    float radius;
    Color sphereColour;  
    Vector3 velocity;
    float mass;
    float restitution;
}Sphere;

typedef struct {
    Vector3 position1;
    Vector3 position2;
    Vector3 position3;
    Color planeColour;  
}Plane;

    const int numSpheres = 1;
    const int numPlanes = 1;

void SphereToSphere(Sphere *sphere1, Sphere *sphere2)
{   
    Vector3 p1 = sphere1->position;
    Vector3 p2 = sphere2->position;
    float r1 = sphere1->radius;
    float r2 = sphere2->radius;
    Vector3 v1 = sphere1->velocity;
    Vector3 v2 = sphere2->velocity;
    float a = Vector3LengthSqr(Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime()));
    float b = Vector3DotProduct(Vector3Subtract(p1, p2), Vector3Scale(Vector3Subtract(v1, v2), GetFrameTime() * 2));
    float c = (Vector3LengthSqr(Vector3Subtract(p1, p2)) - (r1 + r2) * (r1 + r2));
    float t = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);      

    if (t < 1 && t > 0)
    {
        printf("%f\nHit\n", t);
        
        Vector3 momentum = Vector3Add(Vector3Scale(sphere1->velocity,sphere1->mass),Vector3Scale(sphere2->velocity,sphere2->mass));
        printf("%f\nBefore collision ^\n", Vector3Length(momentum));  
        
        Vector3 g = Vector3Normalize(Vector3Subtract(sphere2->position, sphere1->position));       
        Vector3 vr = Vector3Subtract(sphere1->velocity, sphere2->velocity);
        float vj = -(1 + sphere1->restitution * sphere2-> restitution) * Vector3DotProduct(vr, g);     
        float j = vj / (1 / sphere1->mass + 1 / sphere2->mass);
        
        sphere1->velocity = Vector3Add(sphere1->velocity, Vector3Scale(g, j * 1 / sphere1->mass));
        
        Vector3 momentum1 = Vector3Scale(sphere1->velocity, sphere1->mass);
                    
        Vector3 momentum2 = Vector3Subtract(momentum, momentum1);
             
        sphere2->velocity = Vector3Scale(momentum2, 1 / sphere2->mass);                     

        momentum = Vector3Add(Vector3Scale(sphere1->velocity,sphere1->mass),Vector3Scale(sphere2->velocity,sphere2->mass));
        printf("%f\nAfter collision ^\n", Vector3Length(momentum));  
        
        return;
    }
}

void SphereToPlane(Sphere *sphere, Plane *plane)
{
    Vector3 p1 = plane->position1;
    Vector3 p2 = plane->position2;
    Vector3 p3 = plane->position3;
    Vector3 v1 = Vector3Subtract(p2, p1);
    Vector3 v2 = Vector3Subtract(p3, p1);
    Vector3 n = Vector3CrossProduct(v1, v2);
    n = Vector3Normalize(n);
    Vector3 v = sphere->velocity;
    float s1 = acosf(Vector3DotProduct(Vector3Negate(Vector3Normalize(v)), n));  
    printf("%f\n", Vector3Length(n));
    printf("%f\n", n.y);
    
    if( s1 < 90)
    {
        printf("Hit Plane\n");
        printf("%f\n", s1);
    }
    
    Vector3 k = plane->position1;
    Vector3 p = Vector3Add(k, sphere->position);
    float q1 = acosf(Vector3DotProduct(n, Vector3Normalize(p)));
    float q2 = acosf(Vector3DotProduct(Vector3Normalize(p), k));
    
    float r = sphere->radius;
    float d = cosf(s1) * Vector3Length(p);
    float s = Vector3DotProduct(v, Vector3Negate(n));
    
    //Vector3 col = Vector3Scale(p, d) * d - r;
    //Vector3 vc = Vector3Subtract(sphere->position, col);##
    //vc = Vector3Length((d - r) / acosf(s));
    //
    //if (Vector3Length(vc) <= Vector3Length(v))
    //{
    //    printf("%f\n", Vector3Length(vc));
    //    printf("%f\n", Vector3Length(v));
    //    printf("Hit Plane");
    //    return;
    //}
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "SphereToSphere");

    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    
    Plane planes[numPlanes];
    planes[0].position1 = (Vector3){3.0f, 0.0f, -3.0f};
    planes[0].position2 = (Vector3){-3.0f, 0.0f, -3.0f};
    planes[0].position3 = (Vector3){3.0f, 0.0f, 3.0f};
    planes[0].planeColour = RED;
    
    //planes[1].positionX = (Vector3){-5.0f, 0.0f, 0.0f};
    //planes[1].positionY = (Vector3){0.0f, -10.0f, 0.0f};
    //planes[1].positionZ = (Vector3){0.0f, 0.0f, -10.0f};
    //planes[1].planeColour = RED;
    
    Sphere spheres[numSpheres];
    spheres[0].position = (Vector3){0.0f, 5.0f, 0.0f};
    spheres[0].radius = (float){3.0f};
    spheres[0].sphereColour = GREEN;
    spheres[0].velocity = (Vector3){-0.5f, -0.5f, 0.0f};
    spheres[0].mass = (float){5.0f};
    spheres[0].restitution = (float){0.9f};
    
    //spheres[1].position = (Vector3){-5.0f, 0.0f, 0.0f};
    //spheres[1].radius = (float){1.5f};
    //spheres[1].sphereColour = RED;
    //spheres[1].velocity = (Vector3){2.0f, -0.5f, 0.0f};
    //spheres[1].mass = (float){20.0f};
    //spheres[1].restitution = (float){0.9f};
    //
    //spheres[2].position = (Vector3){5.0f, 5.0f, 0.0f};
    //spheres[2].radius = (float){1.5f};
    //spheres[2].sphereColour = YELLOW;
    //spheres[2].velocity = (Vector3){-2.0f, -0.5f, 0.0f};
    //spheres[2].mass = (float){8.0f};
    //spheres[2].restitution = (float){0.9f};
    //
    //spheres[3].position = (Vector3){-5.0f, 5.0f, 0.0f};
    //spheres[3].radius = (float){2.5f};
    //spheres[3].sphereColour = PINK;
    //spheres[3].velocity = (Vector3){2.0f, 0.0f, 0.0f};
    //spheres[3].mass = (float){2.0f};
    //spheres[3].restitution = (float){0.9f};
    
    while (!WindowShouldClose())
    {
        for (int i = 0; i < numSpheres - 1 ; i++)
        {
            for (int j = i + 1; j < numSpheres; j++)
            {
                SphereToSphere(&spheres[i], &spheres[j]);
            }
        }
          
        SphereToPlane(&spheres[0], &planes[0]);  
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
                
            BeginMode3D(camera);                

            for(int i = 0; i < numSpheres; i++)
            {
                DrawSphere(spheres[i].position, spheres[i].radius, spheres[i].sphereColour);
                DrawSphereWires(spheres[i].position, spheres[i].radius, 16, 16, BLACK);
                spheres[i].position = Vector3Add(spheres[i].position, Vector3Scale(spheres[i].velocity, GetFrameTime()));
            }
                         
            for(int i = 0; i < numPlanes; i++)
            {
                DrawTriangle3D(planes[i].position1, planes[i].position2, planes[i].position3, planes[i].planeColour);
            }             
            
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}