#include "Entities/Lander.h"
#include <cmath> 

Vector2 createVector2_Side(float x, float y) // RayLib Vector2 has no constructor, so I use this when creating new vectors
{
    Vector2 vec;
    vec.x = x;
    vec.y = y;

    return vec; 
}

Vector2 Euler_Side(Vector2 a, float h)
{
    return createVector2_Side(a.x * h, 0.0f);
}

void SetForce_Side(Ship& ship)
{
    ship.f.x = ship.Thrust.x * ship.mass;    
}

void ApplyEuler_Side(Ship& ship, float dealtaTime)
{  
    ship.dv = Euler_Side(createVector2_Side(ship.f.x / ship.mass, 0.0f), dealtaTime);      
    ship.v.x = ship.v.x + ship.dv.x;
    ship.dr.x = ship.v.x * dealtaTime; 
    ship.position.x += ship.dr.x;    
}

void ApplySideBoosters(Ship& ship, float dealtTime)
{
    SetForce_Side(ship);
    ApplyEuler_Side(ship, dealtTime);
}