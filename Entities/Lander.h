#ifndef Lander_H // header guard
#define Lander_H
#include <raylib.h>

struct Ship
{
    Texture2D texture;
    Rectangle rec;   
    
    const float Thrust_value = 1.3f;
    const float SideThrust_Value = 0.1f;
    const float RequiredLandingSpeed = -15.0f;

    Vector2 Thrust;  
    float mass;
    Vector2 f; // Force
    Vector2 position;
    Vector2 dr; //Position Change within the frame
    Vector2 v; //Current Speed
    Vector2 dv; //Speed changed within the frame

    float fuel = 100.0f;
    float engine_FuelConsumption = 0.5f;
};
#endif //TICKET_H