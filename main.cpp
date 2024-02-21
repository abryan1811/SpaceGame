#include "main.h"

int main()
{
    int windowWidth = 1500;
    int windowHeight = 800;
    char Title[]{"SpaceHopper"}; 

    //Space Ship Texture
    //Texture2D ship = LoadTexture("Assets/ship.png");

    Character shipData;
    shipData.position.x = windowWidth / 2;
    shipData.position.y = windowHeight - shipData.texture.height;
    // shipData.rec.width= ship.width;
    // shipData.rec.height = ship.height;


    InitWindow(windowWidth, windowHeight, Title);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(windowWidth/2, windowHeight - 100 - 100, 50, 100, BLUE);

        DrawRectangle(0, windowHeight - 100, windowWidth, 50, WHITE);

        EndDrawing();
    }

    CloseWindow();
}
