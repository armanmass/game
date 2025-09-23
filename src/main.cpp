#include <raylib.h>
#include <raylib-cpp.hpp>

#include "Game.hpp"
#include "Settings.hpp"

int main()
{
    InitWindow(Settings::windowWidth, Settings::windowHeight, "C++ Game");
    SetTargetFPS(60);

    Game game{};

    while (!WindowShouldClose())
    {
        game.HandleInput();

        BeginDrawing();
        ClearBackground(Settings::backgroundColor);

        game.Draw();
        game.Update();

        EndDrawing();
    }

    CloseWindow();
}