#include "main.h"

int main() {
    int windowWidth = 800;
    int windowHeight = 800;
    char Title[]{"SpaceHopper"};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, Title);

    //Space Background
    Texture2D spaceBackground = LoadTexture("Assets/backgroundImage.png");
    //// spaceBackgrounds original size
    Rectangle sourceSpaceBGRec = {0.0f, 0.0f, (float)spaceBackground.width, (float)spaceBackground.height};
    //// spaceBackrgounds updated size
    Rectangle destinationSpaceBGRec = {0.0f, 0.0f, (float)windowWidth, (float)windowHeight};

    Vector2 backgroundOrigin = {0.0f, 0.0f};
    
    // Load the spaceship texture
    
    Character shipData;
    shipData.texture = LoadTexture("Assets/ship.png"); 
    float scale = 4.0f;
    float scaledHeight = shipData.texture.height * scale;
    

    //Object Locations
    shipData.position.x = windowWidth / 2 - scaledHeight / 2; // Center the ship
    float floorPositionY = windowHeight - 50;
    shipData.position.y = floorPositionY - scaledHeight + 55;  

    // Use to check the ship has a safe landing
    const float StarterPosition = shipData.position.y;

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(spaceBackground, sourceSpaceBGRec, destinationSpaceBGRec, backgroundOrigin, 0.0f, WHITE);

        // Draw the spaceship texture
        DrawTextureEx(shipData.texture, shipData.position, 0.0f, scale, WHITE);

        // Draw the ground rectangle
        DrawRectangle(0, floorPositionY, windowWidth, 10, WHITE);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(shipData.texture); // Unload the texture
    CloseWindow(); // Close the window

    return 0;
}
