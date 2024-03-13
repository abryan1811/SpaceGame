#include "MovementController.h"

MovementController::MovementController(float moveSpeed, float initialAltitude) 
        : moveSpeed(moveSpeed), initialAltitude(initialAltitude) {}

void MovementController::UpdatePosition(Ship& ship, float& altitudeCounter, float deltaTime, Vector2 gravity)
{    
    if (IsKeyDown(KEY_W) && altitudeCounter > 0.0f) //Activate thrusters
    {
        if(ship.Thrust.y <= 30)
        {
            ship.Thrust.y += 2.3f * deltaTime; 
        }         
    }

    if(!IsKeyDown(KEY_W)) // Removes upwards inertia after thruster's stop
    {
        if(ship.Thrust.y >= 0)
        {
            ship.Thrust.y =- 5.3f;
        }        
    }
}