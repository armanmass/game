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
        BeginDrawing();
        ClearBackground(Settings::backgroundColor);

        game.HandleInput();
        game.Draw();
        game.Update();

        EndDrawing();
    }

    CloseWindow();
}