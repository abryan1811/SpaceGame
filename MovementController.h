#include "raylib.h"

class MovementController{
    public:
    MovementController(float moveSpeed, float initialAltitude);

    // These are in here as references so we dont copy the arguments when we call them in 
    // main as we only need the ones in main shipdata's position and the heightCounter in there)
    void UpdatePosition(Vector2& position, float& altitudeCounter, float deltaTime);

    private:
    float moveSpeed;
    float initialAltitude;
};