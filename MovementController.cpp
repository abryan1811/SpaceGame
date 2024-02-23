#include "MovementController.h"

MovementController::MovementController(float moveSpeed, float initialAltitude) 
        : moveSpeed(moveSpeed), initialAltitude(initialAltitude) {}

void MovementController::UpdatePosition(Vector2& position, float& altitudeCounter, float deltaTime){
    if (IsKeyDown(KEY_W) && altitudeCounter < 100) {
            position.y -= moveSpeed * deltaTime;
        }

        // This finds the highest the ship can go to, compares it to where the ship is, if it matches up, it stops it going any higher
        altitudeCounter = 100.0f * (initialAltitude - position.y) / initialAltitude;

        if (altitudeCounter > 100.0f) 
        {
            altitudeCounter = 100.0f;
            position.y = 0;
        }
}