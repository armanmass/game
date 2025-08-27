#include <raylib.h>
#include <raylib-cpp.hpp>
#include "Settings.hpp"

int main()
{
    InitWindow(Settings::windowWidth, Settings::windowHeight, "C++ Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
}