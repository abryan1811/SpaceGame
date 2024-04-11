#include "Gravity.h"
#include<iostream>


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

Vector2 Gravity = createVector2(0.0f, -5.625f);

void Collision_Sky(Ship& ship)
{
    ship.v.y -= ship.v.y; 
    ship.f.y = (ship.f.y - 10) - ship.f.y;
}
 
void Collision_Ground(Ship& ship)
{ 
   ship.v.y -= ship.v.y; 
   ship.f.y = (ship.f.y + 10) - ship.f.y;    
}

void Collision_Left(Ship& ship)
{
    ship.v.x -= ship.v.x;
    ship.f.x = (ship.f.x + 5) - ship.f.x;
}

void Collision_Right(Ship& ship)
{
    ship.v.x -= ship.v.x;
    ship.f.x = (ship.f.x - 5) - ship.f.x;
}

void CheckCollision(Ship& ship)
{
    if(ship.position.y >= 658.0f && ship.v.y < 0.0f )
    {
        Collision_Ground(ship); 
    }

    if(ship.position.y <= 0.0f && ship.v.y > 0.0f )
    {
        Collision_Sky(ship);
    }

    if(ship.position.x <= -20.0f && ship.v.x < 0.0f)
    {
        Collision_Left(ship);
    }
    
    if(ship.position.x >= 700.0f && ship.v.x > 0.0f)
    {
        Collision_Right(ship);
    }
}

void SetForce(Ship& ship)
{    
    ship.f.y = (Gravity.y + ship.Thrust.y) * ship.mass;    

    CheckCollision(ship);
}

void ApplyEuler(Ship& ship, float deltaTime)
{    
    ship.dv = Euler(createVector2(0.0f, ship.f.y * 1 / ship.mass), deltaTime);
    ship.v.y = ship.v.y + ship.dv.y;
    ship.dr.y =  ship.v.y * deltaTime; 
    ship.position.y = ship.position.y - ship.dr.y;      
}

void ApplyGravity(Ship& ship, float deltaTime)
{   
       SetForce(ship);
       ApplyEuler(ship, deltaTime);    
}