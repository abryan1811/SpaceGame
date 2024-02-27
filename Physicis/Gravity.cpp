#include<iostream>
#include "Entities/Lander.h"

Vector2 createVector2(float x, float y) // RayLib Vector2 has no constructor, so I use this when creating new vectors
{
    Vector2 vec;
    vec.x = x;
    vec.y = y;

    return vec; 
}

Vector2 Euler(Vector2 a, float h)
{
    return createVector2(0.0f, a.y * h);    
}

const Vector2 Gravity = createVector2(0.0f, -100.625f);
// Vector2 Thrust = createVector2(0.0f, 0.0f);

void ApplyGravity(Ship& ship, float dealtaTime)
{
    SetForce(ship);
    ApplyEuler(ship, dealtaTime);
}

void SetForce(Ship& ship)
{    
    ship.f.y = (Gravity.y + ship.Thrust.y) * ship.mass;
}

void ApplyEuler(Ship& ship, float deltaTime)
{
    ship.dv = Euler(createVector2(0.0f, ship.f.y * 1 / ship.mass), deltaTime);
    ship.v.y = ship.v.y + ship.dv.y;
    ship.dr.y =  ship.dv.y * deltaTime; 
    ship.position.y = ship.position.y - ship.dr.y;    
}