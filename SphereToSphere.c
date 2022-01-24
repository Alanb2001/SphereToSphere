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

typedef struct {
    Vector3 position;
    Vector2 size;
    Color planeColour;  
}Plane;

    const int numSpheres = 4;
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
 
    //printf("%f, %f, %f\n ", a, b, c);
    //if (b * b - 4 * a * c < 0)         
    //    return;
                
    float t1 = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);           
  
    if (t1 < 1 && t1 > 0)
    {
        printf("%f\nHit\n",t1);
        
        float momentumX = sphere1->velocity.x * sphere1->mass + sphere2->velocity.x * sphere2->mass;
        float momentumY = sphere1->velocity.y * sphere1->mass + sphere2->velocity.y * sphere2->mass;
        float momentumZ = sphere1->velocity.z * sphere1->mass + sphere2->velocity.z * sphere2->mass;
        printf("%f %f %f\n",momentumX,momentumY,momentumZ);
        float momentum = Vector3Length(Vector3Add(Vector3Scale(sphere1->velocity,sphere1->mass),Vector3Scale(sphere2->velocity,sphere2->mass)));
        printf("%f\n",momentum);  
        
        sphere1->position = Vector3Add(sphere1->position, Vector3Scale(sphere1->velocity, GetFrameTime() * t1));
        sphere2->position = Vector3Add(sphere2->position, Vector3Scale(sphere2->velocity, GetFrameTime() * t1));
        
        Vector3 g = Vector3Normalize(Vector3Subtract(sphere2->position, sphere1->position));
        float q = Vector3DotProduct(v1, g) * (Vector3Length(v1) / sphere2->mass);
        float q2 = Vector3DotProduct(v2, g) * (Vector3Length(v2) / sphere1->mass);
        
        sphere1->velocity = Vector3Add(sphere1->velocity, Vector3Scale(g, q2));        
        sphere1->velocity = (Vector3) 
        { 
        (sphere1->velocity.x * sphere1->mass + sphere2->velocity.x * sphere2->mass) / sphere1->mass,
        (sphere1->velocity.y * sphere1->mass + sphere2->velocity.y * sphere2->mass) / sphere1->mass,
        (sphere1->velocity.z * sphere1->mass + sphere2->velocity.z * sphere2->mass) / sphere1->mass
        };
        
        float momentumX1 = sphere1->velocity.x * sphere1->mass;
        float momentumY1 = sphere1->velocity.y * sphere1->mass;
        float momentumZ1 = sphere1->velocity.z * sphere1->mass;
                    
        float momentumX2 = momentumX - momentumX1;
        float momentumY2 = momentumY - momentumY1;
        float momentumZ2 = momentumZ - momentumZ1;
                                                                 
        sphere2->velocity.x = momentumX2 / sphere2->mass;                     
        sphere2->velocity.y = momentumY2 / sphere2->mass; 
        sphere2->velocity.z = momentumZ2 / sphere2->mass;
        
        //sphere2->velocity = Vector3Add(sphere2->velocity, Vector3Scale(g, q)); 
        //sphere2->velocity = (Vector3) 
        //{ 
        //(sphere2->velocity.x * sphere2->mass - sphere1->velocity.x * sphere1->mass) / sphere2->mass,
        //(sphere2->velocity.y * sphere2->mass - sphere1->velocity.y * sphere1->mass) / sphere2->mass,
        //(sphere2->velocity.z * sphere2->mass - sphere1->velocity.z * sphere1->mass) / sphere2->mass
        //};
               
        momentumX = sphere1->velocity.x * sphere1->mass + sphere2->velocity.x * sphere2->mass;
        momentumY = sphere1->velocity.y * sphere1->mass + sphere2->velocity.y * sphere2->mass;
        momentumZ = sphere1->velocity.z * sphere1->mass + sphere2->velocity.z * sphere2->mass;
        printf("%f %f %f\n",momentumX,momentumY,momentumZ);
        momentum = Vector3Length(Vector3Add(Vector3Scale(sphere1->velocity,sphere1->mass),Vector3Scale(sphere2->velocity,sphere2->mass)));
        printf("%f\n",momentum);  
        
        return;
    }
}

void SphereToPlane(Sphere *sphere, Plane *plane)
{
    Vector3 n = plane->position;
    Vector3 v = sphere->velocity;
    Vector3 k = plane->position;
    Vector3 p = Vector3Add(k, sphere->position);
    //float s1 = Vector3Angle(n, -v);
    Vector2 q1 = Vector3Angle(n, p);
    Vector2 q2 = Vector3Angle(p, k);
    //Vector3 q3 = Vector3Add(q1, q2);
    
    float r = sphere->radius;
    
    //float d = Mathf.Sin(q2) % p.sqrMagnitude;
    //float s = Vector3.Angle(v, -n);
    //float vc = (d - r) / Mathf.Cos(s);
    
    //if (q3 < 90 && vc <= v.magnitude)
    //{
    //    print(q3);
    //    print(vc);
    //    print(v);
    //    print("Hit Plane");
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
    planes[0].position = (Vector3){0.0f, 0.0f, 0.0f};
    planes[0].size = (Vector2){1.5f, 1.5f};
    planes[0].planeColour = RED;
    
    Sphere spheres[numSpheres];
    spheres[0].position = (Vector3){5.0f, 0.0f, 0.0f};
    spheres[0].radius = (float){3.0f};
    spheres[0].sphereColour = GREEN;
    spheres[0].velocity = (Vector3){-2.0f, -0.5f, 0.0f};
    spheres[0].mass = (float){5.0f};
    
    spheres[1].position = (Vector3){-5.0f, 0.0f, 0.0f};
    spheres[1].radius = (float){1.5f};
    spheres[1].sphereColour = RED;
    spheres[1].velocity = (Vector3){2.0f, -0.5f, 0.0f};
    spheres[1].mass = (float){20.0f};

    spheres[2].position = (Vector3){5.0f, 5.0f, 0.0f};
    spheres[2].radius = (float){1.5f};
    spheres[2].sphereColour = YELLOW;
    spheres[2].velocity = (Vector3){-2.0f, -0.5f, 0.0f};
    spheres[2].mass = (float){5.0f};
    
    spheres[3].position = (Vector3){-5.0f, 5.0f, 0.0f};
    spheres[3].radius = (float){0.5f};
    spheres[3].sphereColour = PINK;
    spheres[3].velocity = (Vector3){2.0f, -0.5f, 0.0f};
    spheres[3].mass = (float){1.0f};
    
    while (!WindowShouldClose())
    {
        for (int i = 0; i < numSpheres - 1 ; i++)
        {
            for (int j = i + 1; j < numSpheres; j++)
            {
                SphereToSphere(&spheres[i], &spheres[j]);
            }
        }

        //SphereToSphere(&spheres[0], &spheres[1]);
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
                
            BeginMode3D(camera);                

            for(int i = 0; i < numSpheres; i++)
            {
                DrawSphere(spheres[i].position, spheres[i].radius, spheres[i].sphereColour);
                DrawPlane(planes[0].position, planes[0].size, planes[0].planeColour);
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