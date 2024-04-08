#include "Physicis/Gravity.cpp"
#include "Physicis/SideBoosters.cpp"
#include "StartMenu.h"
#include "ObstacleCollisions.h"
#include "Physicis/PID.h"
   
bool CheckTouchDown(Ship& ship)
{
    if(ship.position.y >= 658.0f && ship.v.y < 0.0f )
    {                
        if(ship.v.y > ship.RequiredLandingSpeed ) // Required landing speed
        {
            return true;
        }               
    }

    return false;    
}

void SuccessMessage()
{
    BeginDrawing();
    ClearBackground(BLACK);           
    DrawText("Mission Success!", 50, 400, 100, GREEN);
    EndDrawing();
}

void FailMessage()
{
    BeginDrawing();
    ClearBackground(BLACK);           
    DrawText("Game Over!", 50, 400, 100, RED);
    EndDrawing();
}

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
    shipData.animatedTexture = LoadTexture("Assets/engineSpriteSheet.png");
    float scale = 2.0f;
    float scaledHeight = shipData.texture.height * scale;
    
    //Object Locations
    shipData.position.x = windowWidth / 2 - scaledHeight / 2; // Center the ship
    float floorPositionY = windowHeight - 50;
    // shipData.position.y = floorPositionY - scaledHeight + 20; 
    shipData.position.y = 10.0f; 
    // shipData.mass = 2.0f; 

    shipData.dr.y = 0.0f;
    shipData.dr.x = 0.0f;

    shipData.v.y = 0.0f;
    shipData.v.x = 0.0f;

    shipData.dv.y = 0.0f;
    shipData.dv.x = 0.0f;

    shipData.Thrust.y = 0.0f;    

    // Use to check the ship has a safe landing
    const float StarterPosition = shipData.position.y;

    bool isGameOver_Fail = false;
    bool isGameOVer_Success = false;

    const float moveSpeed = 100.0f;
    float deltaTime = 0.06f; // 1 frame every 0.06ms, reflecting 60fps

    int thrustAnimationFrameIndex = 0;

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
    while (!WindowShouldClose())
    {
        if (!isGameOver_Fail && !isGameOVer_Success)
        {
        BeginDrawing();
        ClearBackground(BLACK);
        
        // Update and Draw Asteroid
        // asteroid.Update(deltaTime);       

        // Reset asteroid position if it goes off-screen
        // if (asteroid.IsOffScreen(windowHeight)) {
        //     int textureWidth = asteroid.texture.width / 16;
        //     asteroid.position.x = GetRandomValue(0, windowWidth - textureWidth);
        //     asteroid.position.y = -asteroid.texture.height;
        // }        
        
        Pid_Controller VerticalBoosterPID;

        float desiredLandingSpeed =  346/17.0f - shipData.position.y/24.0f;
        desiredLandingSpeed = std::min(-desiredLandingSpeed,-1.0f);
        VerticalBoosterPID.SetError(desiredLandingSpeed, shipData.v.y);

        float output_P = VerticalBoosterPID.Get_P_output();
        float output_i = VerticalBoosterPID.Get_I_output(deltaTime);
        float output = output_i + output_P;


        // float output = VerticalBoosterPID.cp * error; 



        // // ship and drawing logic here               
        // movementController.UpdatePosition(shipData, shipData.position.y, deltaTime); 
       
        movementController.AutoLand_Vertical(shipData,output);
        ApplyGravity(shipData, deltaTime); 
        movementController.UpdatePosition_Side(shipData,deltaTime);      
        ApplySideBoosters(shipData, deltaTime); 

        

        



        

        Rectangle shipRect = MovementController::GetShipRectangle(shipData);   
        Rectangle asteroidRect = asteroid.GetAsteroidRectangle();                 

        DrawTexturePro(spaceBackground, sourceSpaceBGRec, destinationSpaceBGRec, backgroundOrigin, 0.0f, WHITE);
        DrawTextureEx(shipData.texture, shipData.position, 0.0f, scale, WHITE);
               

        thrustAnimationFrameIndex = (thrustAnimationFrameIndex + 1) % 8; // Update this each frame to cycle through images 

        Rectangle sourceRec = {
            (float)(thrustAnimationFrameIndex * (shipData.animatedTexture.width / 8)),
            0.0f,
            (float)(shipData.animatedTexture.width / 8),
            (float)shipData.animatedTexture.height
        };

        Rectangle destRec = {
            shipData.position.x,
            shipData.position.y,
            sourceRec.width * scale, 
            sourceRec.height * scale 
        };
      
        Vector2 origin = {0, 0};

        if (movementController.thrustOn){
        // Draw the current frame of the animation with scaling
        DrawTexturePro(shipData.animatedTexture, sourceRec, destRec, origin, 0.0f, WHITE);
        }

        DrawRectangle(0, floorPositionY, windowWidth, 10, WHITE);
        DrawText(TextFormat("Height: %0.2f miles", (windowHeight - shipData.position.y)), 10, 10, 20, WHITE); // THIS IS UPSIDE DOWN... NEEDS FIXING  
        DrawText(TextFormat("Fuel: %0.2f Liters", shipData.fuel), 10, 30, 20, WHITE); 
        DrawText(TextFormat("Speed: %0.2f Vertical", shipData.v.y), 10, 50, 20, WHITE); 
        DrawText(TextFormat("Speed: %0.2f Vertical", output), 10, 70, 20, RED);  
        DrawText(TextFormat("Height: %0.2f Vertical", shipData.position.y), 10, 90, 20, GREEN);       
        
        if (CheckCollisionRecs(shipRect, asteroidRect))
        {
            // Just for testing, will need to add destruction of ship and replace with explosion.
            isGameOver_Fail = true;
        }                      

        asteroid.Draw(); 
           
        EndDrawing();
        }     
        
        else if (isGameOver_Fail == true)
        {
            FailMessage();
        }       

    if(shipData.position.y >= 658.0f && shipData.v.y < 0.0f )
    {
        isGameOVer_Success= CheckTouchDown(shipData);
        
        switch (isGameOVer_Success == true)
        {
            case true:
            SuccessMessage();
            break;
        
            case false:
            isGameOver_Fail = true;
            FailMessage();        
            break;
        }
    }
    }

    // De-Initialization
    UnloadTexture(shipData.texture); // Unload the texture
    CloseWindow(); // Close the window

    return 0;
}
