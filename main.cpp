#include "raylib.h"
#include "core/Config.h"

int main()
{


    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,GAME_NAME);

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