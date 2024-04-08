#include "Entities/Lander.h"

class MovementController{
    public:
    MovementController(float moveSpeed, float initialAltitude);

    // These are in here as references so we dont copy the arguments when we call them in 
    // main as we only need the ones in main shipdata's position and the heightCounter in there)
    void UpdatePosition_1(Ship& ship1, float& altitudeCounter1, float deltaTime);
    void UpdatePosition_Side_1(Ship& ship, float deltaTime);
    void UpdatePosition_2(Ship& ship2, float altitudeCounter2, float deltaTime);
    void UpdatePosition_Side_2(Ship& ship2, float deltaTime);


    void AutoLand_Vertical(Ship& ship, float pid_output);



    static Rectangle GetShipRectangle(const Ship& ship);
    bool thrustOn_1 = false;
    bool thrustOn_2 = false;

    private:
    float moveSpeed;
    float initialAltitude;
};