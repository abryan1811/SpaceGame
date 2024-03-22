#include "MovementController.h"

 Rectangle MovementController::GetShipRectangle(const Ship& ship) {
        float scale = 2.0f;
        return (Rectangle){ship.position.x, ship.position.y, ship.texture.width * scale, ship.texture.height * scale };
    }

MovementController::MovementController(float moveSpeed, float initialAltitude) 
        : moveSpeed(moveSpeed), initialAltitude(initialAltitude) {}

void MovementController::UpdatePosition(Ship& ship, float& altitudeCounter, float deltaTime, Vector2 gravity)
{    
    if (IsKeyDown(KEY_W) && altitudeCounter > 0.0f && ship.fuel > 0 ) //Activate thrusters
    {
        if(ship.Thrust.y <= 25)
        {
            ship.Thrust.y += ship.Thrust_value;             
        }

        ship.fuel -= ship.engine_FuelConsumption;  
    }

    else // Removes upwards inertia after thruster's stop
    {
         ship.Thrust.y = 0.0f;             
    }
}