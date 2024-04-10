#include "Physicis/Gravity.cpp"
#include "Physicis/SideBoosters.cpp"
#include "StartMenu.h"
#include "ObstacleCollisions.h"
#include "Physicis/PID.h"
#include <thread>
#include <vector>

std::vector<Ship> Ships;
bool isGameOver_Fail = false;
bool isGameOVer_Success = false;

void CheckTouchDown(Ship &ship1, Ship &ship2)
{
    if ((ship1.position.y >= 658.0f && ship1.v.y < 0.0f) || (ship2.position.y >= 658.0f && ship2.v.y < 0.0f))
    {
        if (ship1.v.y > ship1.RequiredLandingSpeed || ship2.v.y > ship2.RequiredLandingSpeed) // Required landing speed
        {
            isGameOVer_Success = true;
            return;
        }

        isGameOver_Fail = true;
    }
}

void SuccessMessage()
{
    BeginDrawing();
    ClearBackground(BLACK);
    std::string message = "Mission Success!";
    DrawText(message.c_str(), 50, 400, 100, GREEN);
    EndDrawing();
}

void FailMessage()
{
    BeginDrawing();
    ClearBackground(BLACK);
    std::string message = "Mission Failed!";
    DrawText(message.c_str(), 50, 400, 100, RED);
    EndDrawing();
}

void ShipDataInit(Ship &ship1, Ship &ship2)
{
    ship1.dr.y = 0.0f;
    ship1.dr.x = 0.0f;
    ship1.v.y = 0.0f;
    ship1.v.x = 0.0f;
    ship1.dv.y = 0.0f;
    ship1.dv.x = 0.0f;
    ship1.Thrust.y = 0.0f;

    ship2.dr.y = 0.0f;
    ship2.dr.x = 0.0f;
    ship2.v.y = 0.0f;
    ship2.v.x = 0.0f;
    ship2.dv.y = 0.0f;
    ship2.dv.x = 0.0f;
    ship2.Thrust.y = 0.0f;
}

void DisplayGameOver()
{
    if (isGameOVer_Success)
        SuccessMessage();

    if (isGameOver_Fail)
        FailMessage();
}

int main()
{

    int windowWidth = 800;
    int windowHeight = 800;
    char Title[]{"SpaceHopper"};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, Title);
    SetTargetFPS(60);

    GameMenu startMenu;

    // Space Background
    Texture2D spaceBackground = LoadTexture("Assets/backgroundImage.png");
    //// spaceBackgrounds original size
    Rectangle sourceSpaceBGRec = {0.0f, 0.0f, (float)spaceBackground.width, (float)spaceBackground.height};
    //// spaceBackrgounds updated size
    Rectangle destinationSpaceBGRec = {0.0f, 0.0f, (float)windowWidth, (float)windowHeight};

    Vector2 backgroundOrigin = {0.0f, 0.0f};

    // Load the spaceship texture
    Ship shipData1;
    Ships.push_back(shipData1);
    shipData1.m_Name = "Ship1";
    shipData1.texture = LoadTexture("Assets/ship.png");
    shipData1.animatedTexture = LoadTexture("Assets/engineSpriteSheet.png");

    float scale = 2.0f;
    float scaledHeight = shipData1.texture.height * scale;

    Ship shipData2;
    Ships.push_back(shipData2);
    shipData2.m_Name = "Ship2";
    shipData2.texture = LoadTexture("Assets/ship.png");
    shipData2.animatedTexture = LoadTexture("Assets/engineSpriteSheet.png");

    // Object Locations
    shipData1.position.x = windowWidth / 2 - scaledHeight / 2; // Center the ship
    float floorPositionY = windowHeight - 50;
    shipData1.position.y = 10.0f;

    shipData2.position.x = windowWidth / 2 - scaledHeight / 2; // Center the ship
    shipData2.position.x += 20.0f;
    shipData2.position.y = 10.0f;

    ShipDataInit(shipData1, shipData2);

    // Use to check the ship has a safe landing
    const float StarterPosition = shipData1.position.y;

    const float moveSpeed = 100.0f;
    float deltaTime = 0.06f; // 1 frame every 0.06ms, reflecting 60fps

    int thrustAnimationFrameIndex = 0;

    // Asteroid Texture

    Texture2D asteroids = LoadTexture("Assets/animated_asteroid.png");

    Asteroid asteroid({100, -100}, asteroids, 150.0f, 0.5f);

    MovementController movementController(moveSpeed, StarterPosition);

    Pid_Controller VerticalBoosterPID;

    while (!WindowShouldClose())
    {
        startMenu.Update();

        if (startMenu.IsGameStartSelected() && IsKeyPressed(KEY_ENTER))
        {

            break;
        }
        else if (startMenu.IsGameQuitSelected() && IsKeyPressed(KEY_ENTER))
        {

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

            float desiredLandingSpeed = 346 / 17.0f - shipData1.position.y / 24.0f;
            desiredLandingSpeed = std::min(-desiredLandingSpeed, -1.0f);
            VerticalBoosterPID.SetError(desiredLandingSpeed, shipData1.v.y);

            float output_P = VerticalBoosterPID.Get_P_output();
            float output_i = VerticalBoosterPID.Get_I_output(deltaTime);
            float output_d = VerticalBoosterPID.Get_D_output(deltaTime);
            float output = output_i + output_P + output_d;
           

            // // ship and drawing logic here
            // movementController.UpdatePosition_1(shipData1, shipData1.position.y, deltaTime);  //** UNCOMMENT THIS TO BE ABLE TO PLAY WITH THE OTHER SHIP, 
            movementController.AutoLand_Vertical(shipData1, output);
            ApplyGravity(shipData1, deltaTime);
            movementController.UpdatePosition_2(shipData2, shipData2.position.y, deltaTime);
            ApplyGravity(shipData2, deltaTime);

            movementController.UpdatePosition_Side_1(shipData1, deltaTime);
            ApplySideBoosters(shipData1, deltaTime);
            movementController.UpdatePosition_Side_2(shipData2, deltaTime);
            ApplySideBoosters(shipData2, deltaTime);

            Rectangle shipRect1 = MovementController::GetShipRectangle(shipData1);
            Rectangle shipRect2 = MovementController::GetShipRectangle(shipData2);
            Rectangle asteroidRect = asteroid.GetAsteroidRectangle();

            DrawTexturePro(spaceBackground, sourceSpaceBGRec, destinationSpaceBGRec, backgroundOrigin, 0.0f, WHITE);
            DrawTextureEx(shipData1.texture, shipData1.position, 0.0f, scale, WHITE);
            DrawTextureEx(shipData2.texture, shipData2.position, 0.0f, scale, RED);

            thrustAnimationFrameIndex = (thrustAnimationFrameIndex + 1) % 8; // Update this each frame to cycle through images

            Rectangle sourceRec = {
                (float)(thrustAnimationFrameIndex * (shipData1.animatedTexture.width / 8)),
                0.0f,
                (float)(shipData1.animatedTexture.width / 8),
                (float)shipData1.animatedTexture.height};

            Rectangle destRec = {
                shipData1.position.x,
                shipData1.position.y,
                sourceRec.width * scale,
                sourceRec.height * scale};

            Vector2 origin = {0, 0};

            if (movementController.thrustOn_1)
            {
                // Draw the current frame of the animation with scaling
                DrawTexturePro(shipData1.animatedTexture, sourceRec, destRec, origin, 0.0f, WHITE);
            }

            DrawRectangle(0, floorPositionY, windowWidth, 10, WHITE);
            DrawText(TextFormat("Height: %0.2f miles", (windowHeight - shipData1.position.y)), 10, 10, 20, WHITE); // THIS IS UPSIDE DOWN... NEEDS FIXING
            DrawText(TextFormat("Fuel: %0.2f Liters", shipData1.fuel), 10, 30, 20, WHITE);
            DrawText(TextFormat("Speed: %0.2f Vertical", shipData1.v.y), 10, 50, 20, WHITE);
            DrawText(TextFormat("Speed: %0.2f Vertical", output), 10, 70, 20, RED);
            DrawText(TextFormat("position_Y: %0.2f Y", shipData2.position.y), 10, 90, 20, RED);

            CheckTouchDown(shipData1, shipData2);

            asteroid.Draw();

            EndDrawing();
        }

        DisplayGameOver();
    }

    // De-Initialization
    UnloadTexture(shipData1.texture); // Unload the texture
    CloseWindow();                    // Close the window

    return 0;
}
