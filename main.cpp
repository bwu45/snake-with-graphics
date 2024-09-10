#include "raylib.h"
#include "game.h"
#include <deque>

Color lightGreen = {155, 188, 15, 255};
Color green = {48, 98, 48, 255};
Color darkGreen = {15, 56, 15, 255};
Color red = {175, 0, 0, 255};

class Snake
{
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    void draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * CELLSIZE, y * CELLSIZE, (float)CELLSIZE, (float)CELLSIZE};
            DrawRectangleRounded(segment, 0.5, 6, green);
        }
    }
};

class Food
{
public:
    Vector2 position;

    Food()
    {
        position = GenerateRandomPos();
    }

    void draw()
    {
        DrawRectangle(position.x * CELLSIZE, position.y * CELLSIZE, CELLSIZE, CELLSIZE, red); // x, y, width, height, color
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, CELLCOUNT - 1);
        float y = GetRandomValue(0, CELLCOUNT - 1);
        return Vector2{x, y};
    }
};

int main(int argc, char const *argv[])
{
    InitWindow(InitialWidth, InitialHeight, "Snake"); // width, height, window name
    SetTargetFPS(60);

    Food food = Food();
    Snake snake = Snake();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(lightGreen);
        food.draw();
        snake.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
