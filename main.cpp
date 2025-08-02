#include "raylib.h"

int main()
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1200;
    const int TARGET_FPS = 60;

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Slymania");

    SetTargetFPS(TARGET_FPS);


    while(!WindowShouldClose())
    {

        //Start the Window
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Slymania Workspace",450,505,100, BLACK);

        //Close The Window
        EndDrawing();
    }

    CloseWindow();

    return 0;
}