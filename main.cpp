#include "main.h"

int main()
{
    int windowWidth = 1500;
    int windowHeight = 800;
    char Title[]{"SpaceHopper"}; 

    InitWindow(windowWidth, windowHeight, Title);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}
