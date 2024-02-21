#include "main.h"

int main()
{
    int windowWidth = 1500;
    int windowHeight = 800;
    char Title[]{"SpaceHopper"}; 

    //Space Ship Texture
    Character shipData;
    shipData.position.x = windowWidth / 2;
    shipData.position.y = windowHeight - shipData.texture.height;


    InitWindow(windowWidth, windowHeight, Title);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(windowWidth/2, windowHeight-100, 50, 150, WHITE);

        EndDrawing();
    }

    CloseWindow();
}
