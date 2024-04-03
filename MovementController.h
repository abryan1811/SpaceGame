#include "Entities/Lander.h"

class MovementController{
    public:
    MovementController(float moveSpeed, float initialAltitude);

    // These are in here as references so we dont copy the arguments when we call them in 
    // main as we only need the ones in main shipdata's position and the heightCounter in there)
    void UpdatePosition(Ship& ship, float& altitudeCounter, float deltaTime);
    void UpdatePosition_Side(Ship& ship, float deltaTime);
    static Rectangle GetShipRectangle(const Ship& ship);
    bool thrustOn = false;

    private:
    float moveSpeed;
    float initialAltitude;
};