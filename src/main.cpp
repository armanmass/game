#include <raylib.h>
#include <raylib-cpp.hpp>

#include "Game.hpp"
#include "Settings.hpp"
#include "entity/alien/Alien.hpp"

int main()
{
    InitWindow(Settings::windowWidth, Settings::windowHeight, "C++ Game");
    SetTargetFPS(60);

    Game game{};
    Alien alien{1, {100,100}};

    while (!WindowShouldClose())
    {
        game.HandleInput();

        BeginDrawing();
        ClearBackground(Settings::backgroundColor);

        game.Draw();
        alien.Draw();
        game.Update();

        EndDrawing();
    }

    CloseWindow();
}