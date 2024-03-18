#include "Physicis/Gravity.cpp"
#include "StartMenu.h"
#include "ObstacleCollisions.h"


int main() {
    int windowWidth = 800;
    int windowHeight = 800;
    char Title[]{"SpaceHopper"};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, Title);
    SetTargetFPS(60);

    GameMenu startMenu;

    //Space Background
    Texture2D spaceBackground = LoadTexture("Assets/backgroundImage.png");
    //// spaceBackgrounds original size
    Rectangle sourceSpaceBGRec = {0.0f, 0.0f, (float)spaceBackground.width, (float)spaceBackground.height};
    //// spaceBackrgounds updated size
    Rectangle destinationSpaceBGRec = {0.0f, 0.0f, (float)windowWidth, (float)windowHeight};

    Vector2 backgroundOrigin = {0.0f, 0.0f};
    
    // Load the spaceship texture
    
    Ship shipData;
    shipData.texture = LoadTexture("Assets/ship.png"); 
    float scale = 2.0f;
    float scaledHeight = shipData.texture.height * scale;
    
    //Object Locations
    shipData.position.x = windowWidth / 2 - scaledHeight / 2; // Center the ship
    float floorPositionY = windowHeight - 50;
    // shipData.position.y = floorPositionY - scaledHeight + 20; 
    shipData.position.y = 10.0f; 
    shipData.mass = 1.0f; 
    shipData.dr.y = 0.0f;
    shipData.v.y = 0.0f;
    shipData.dv.y = 0.0f;
    shipData.Thrust.y = 0.0f;

    // Use to check the ship has a safe landing
    const float StarterPosition = shipData.position.y;

    const float moveSpeed = 100.0f;
    float deltaTime = 0.06f; // 1 frame every 0.06ms, reflecting 60fps

    // Asteroid Texture

    Texture2D asteroids = LoadTexture("Assets/animated_asteroid.png");

    Asteroid asteroid({400, -100}, asteroids, 150.0f, 0.5f);

    MovementController movementController(moveSpeed, StarterPosition);

    while (!WindowShouldClose()) {
        startMenu.Update();

        if (startMenu.IsGameStartSelected() && IsKeyPressed(KEY_ENTER)){
            
            break;
        }
        else if (startMenu.IsGameQuitSelected() && IsKeyPressed(KEY_ENTER)){
            
            CloseWindow();
            break;
        }

        BeginDrawing();
        startMenu.Draw();
        EndDrawing();
    }
    // Main game loop 
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);
        
        // Update and Draw Asteroid
        asteroid.Update(deltaTime);
       

        // Reset asteroid position if it goes off-screen
        if (asteroid.IsOffScreen(windowHeight)) {
            // ToDo Add replacement asteroids (randomise every asteroid after the first one)
            // I should sort out a reference/pointer here so just one bit of memory is reserved for the asteroids on screen. 
        }

        // // ship and drawing logic here
        ApplyGravity(shipData, deltaTime);        
        movementController.UpdatePosition(shipData, shipData.position.y, deltaTime, Gravity);        
        DrawTexturePro(spaceBackground, sourceSpaceBGRec, destinationSpaceBGRec, backgroundOrigin, 0.0f, WHITE);
        DrawTextureEx(shipData.texture, shipData.position, 0.0f, scale, WHITE);
        DrawRectangle(0, floorPositionY, windowWidth, 10, WHITE);
        DrawText(TextFormat("Height: %0.2f miles", shipData.position.y), 10, 10, 20, WHITE);   
        DrawText(TextFormat("Fuel: %0.2f Liters", shipData.fuel), 10, 30, 20, WHITE); 
        asteroid.Draw();     

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(shipData.texture); // Unload the texture
    CloseWindow(); // Close the window

    return 0;
}
