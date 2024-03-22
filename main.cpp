#include "Physicis/Gravity.cpp"
#include "Physicis/SideBoosters.cpp"
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
    shipData.mass = 2.0f; 

    shipData.dr.y = 0.0f;
    shipData.dr.x = 0.0f;

    shipData.v.y = 0.0f;
    shipData.v.x = 0.0f;

    shipData.dv.y = 0.0f;
    shipData.dv.x = 0.0f;

    shipData.Thrust.y = 0.0f;    

    // Use to check the ship has a safe landing
    const float StarterPosition = shipData.position.y;

    bool isGameOver = false;

    const float moveSpeed = 100.0f;
    float deltaTime = 0.06f; // 1 frame every 0.06ms, reflecting 60fps

    // Asteroid Texture

    Texture2D asteroids = LoadTexture("Assets/animated_asteroid.png");

    Asteroid asteroid({100, -100}, asteroids, 150.0f, 0.5f);

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
        if (!isGameOver){
        BeginDrawing();
        ClearBackground(BLACK);
        
        // Update and Draw Asteroid
        asteroid.Update(deltaTime);       

        // Reset asteroid position if it goes off-screen
        if (asteroid.IsOffScreen(windowHeight)) {
            int textureWidth = asteroid.texture.width / 16;
            asteroid.position.x = GetRandomValue(0, windowWidth - textureWidth);
            asteroid.position.y = -asteroid.texture.height;
        }
        
        
        // // ship and drawing logic here
        ApplyGravity(shipData, deltaTime);        
        movementController.UpdatePosition(shipData, shipData.position.y, deltaTime);     
        Rectangle shipRect = MovementController::GetShipRectangle(shipData);   
        Rectangle asteroidRect = asteroid.GetAsteroidRectangle();

        
        movementController.UpdatePosition_Side(shipData,deltaTime);      
        ApplySideBoosters(shipData, deltaTime);  

        DrawTexturePro(spaceBackground, sourceSpaceBGRec, destinationSpaceBGRec, backgroundOrigin, 0.0f, WHITE);
        DrawTextureEx(shipData.texture, shipData.position, 0.0f, scale, WHITE);
        DrawRectangle(0, floorPositionY, windowWidth, 10, WHITE);
        //DrawText(TextFormat("Height: %0.2f miles", shipData.position.y), 10, 10, 20, WHITE);   
        DrawText(TextFormat("Fuel: %0.2f Liters", shipData.fuel), 10, 30, 20, WHITE); 
        DrawText(TextFormat("Fuel: %0.2f Liters", shipData.fuel), 10, 30, 20, WHITE);     
        DrawText(TextFormat("side: %0.2f ", shipData.position.x), 10, 40, 20, WHITE);   
        DrawText(TextFormat("forceX: %0.2f ", shipData.f.x), 10, 70, 20, WHITE);
        DrawText(TextFormat("ThrustX: %0.2f ", shipData.Thrust.x), 10, 85, 20, WHITE);
       
        if (CheckCollisionRecs(shipRect, asteroidRect)){
            // Just for testing, will need to add destruction of ship and replace with explosion.
            isGameOver = true;
        }

        
           asteroid.Draw(); 
           
           EndDrawing();
        }     
        
        else if (isGameOver){
            BeginDrawing();
            ClearBackground(BLACK);           
            DrawText("Game Over!", 50, 400, 100, RED);
            EndDrawing();
        }
    }

    // De-Initialization
    UnloadTexture(shipData.texture); // Unload the texture
    CloseWindow(); // Close the window

    return 0;
}
