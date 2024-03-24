#include "MovementController.h"

 Rectangle MovementController::GetShipRectangle(const Ship& ship) {
        float scale = 2.0f;
        return (Rectangle){ship.position.x, ship.position.y, ship.texture.width * scale, ship.texture.height * scale };
    }

MovementController::MovementController(float moveSpeed, float initialAltitude) 
        :  initialAltitude(initialAltitude) {}

void MovementController::UpdatePosition(Ship& ship, float& altitudeCounter, float deltaTime)
{    
    if (IsKeyDown(KEY_W) && altitudeCounter > 0.0f && ship.fuel > 0 ) //Activate thrusters
    {
        if(ship.Thrust.y <= 20)
        {
            ship.Thrust.y += ship.Thrust_value;             
        }

        ship.fuel -= ship.engine_FuelConsumption;  
    }    
    
    else // Removes upwards inertia after thruster's stop
    {
        ship.Thrust.y = 0.0f;

        if(ship.v.y > 0 )
        {
            ship.v.y -= 0.5f;
        }                    
    }
}

void MovementController::UpdatePosition_Side(Ship& ship, float deltaTime)
{
    if (IsKeyDown(KEY_A) && ship.fuel > 0) //MOVING LEFT
    {  
        if(ship.Thrust.x > -7)
        {
            ship.Thrust.x -= ship.SideThrust_Value; 
        }                             
    }

    else if (IsKeyDown(KEY_D) && ship.fuel > 0) //MOVING RIGHT
    {  
        if(ship.Thrust.x < 7)
        {            
            ship.Thrust.x += ship.SideThrust_Value;  
        }                             
    }

    else
    {  
        ship.Thrust.x = 0.0f;      
        ship.v.x = 0.0f;
    }
}