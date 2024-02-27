#include "MovementController.h"

MovementController::MovementController(float moveSpeed, float initialAltitude) 
        : moveSpeed(moveSpeed), initialAltitude(initialAltitude) {}

void MovementController::UpdatePosition(Ship& ship, float& altitudeCounter, float deltaTime, Vector2 gravity)
{
    if (IsKeyDown(KEY_W) && altitudeCounter < 100 && ship.Thrust.y <= 10) 
    {
        ship.Thrust.y += 3.5f * deltaTime;  
    }
    else
    {
        if(ship.Thrust.y >= 0)
        {
            ship.Thrust.y += (gravity.y * 9) * deltaTime;
        }        
    }

    //     // This finds the highest the ship can go to, compares it to where the ship is, if it matches up, it stops it going any higher
    //     // altitudeCounter = 100.0f * (initialAltitude - position.y) / initialAltitude;

    //     // if (altitudeCounter > 100.0f) 
    //     // {
    //     //     altitudeCounter = 100.0f;
    //     //     position.y = 0;
    //     // }
}

