#include "raylib.h"
#include "game.h"
#include "raymath.h"
#include <deque>

Color lightGreen = {173, 204, 96, 255};
Color green = {48, 98, 48, 255};
Color darkGreen = {15, 56, 15, 255};
Color red = {175, 0, 0, 255};

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

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

    void update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
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

class Game
{
public:
    Snake snake = Snake();
    Food food = Food();

    void draw()
    {
        food.draw();
        snake.draw();
    }

    void update()
    {
        snake.update();
    }

    void movement()
    {
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
        {
            snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction = {1, 0};
        }
    }
};

int main(int argc, char const *argv[])
{
    InitWindow(InitialWidth, InitialHeight, "Snake"); // width, height, window name
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (eventTriggered(0.2))
        {
            game.update();
        }

        ClearBackground(lightGreen);
        game.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
