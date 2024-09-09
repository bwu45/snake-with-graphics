#include "raylib.h"
#include "game.h"
#include <iostream>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int main(int argc, char const *argv[])
{
    std::cout << "Starting game..." << std::endl;
    InitWindow(InitialWidth, InitialHeight, "Snake"); //width, height, window name 
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
