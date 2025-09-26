#include <Functions.hpp>
#include <raylib.h>
#include <raylib-cpp.hpp>
#include <string>

#include "Game.hpp"
#include "Settings.hpp"

int main()
{
    InitWindow(Settings::windowWidth + 2*Settings::horizOffset, Settings::windowHeight + 2*Settings::vertOffset, "C++ Game");
    SetTargetFPS(60);

    Game game{};
    Font font = LoadFont("assets/fonts/Valorant.ttf");
    Texture2D livesImage = LoadTexture("assets/spaceship/sage.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Settings::backgroundColor);

        DrawRectangleRoundedLines({Settings::horizOffset, Settings::vertOffset - 60.0f, 
                                    Settings::windowWidth, Settings::windowHeight + 120.0f}, 
                                    0.18f, 20, Settings::playerColor);        
        DrawLineEx({2*Settings::horizOffset, Settings::windowHeight+Settings::vertOffset},
                   {Settings::windowWidth, Settings::windowHeight+Settings::vertOffset},
                   3.0f, Settings::playerColor);

        std::string levelStatus = game.isRunning() ? "LEVEL 01" : "GAME OVER";
        DrawTextEx(font, levelStatus.c_str(), 
                {Settings::windowWidth-12*Settings::horizOffset, 
                Settings::windowHeight+1.15f*Settings::vertOffset},
                40, 2, Settings::playerColor);
        
        for (int i{}; i<game.getLives(); ++i)
        {
            float xPos = (2.75f+2*i)*Settings::horizOffset;
            DrawTextureEx(livesImage, 
                {xPos, Settings::windowHeight+1.05f*Settings::vertOffset},
                0.0f, 0.1f, WHITE);
        }

        DrawTextEx(font, "SCORE: ", {2*Settings::horizOffset, 0.65f*Settings::vertOffset},
                   40, 2, Settings::playerColor);
        DrawTextEx(font, std::to_string(game.getScore()).c_str(), 
                   {8.5f*Settings::horizOffset, 0.65f*Settings::vertOffset},
                   40, 2, Settings::playerColor);

        game.HandleInput();
        game.Draw();
        game.Update();

        EndDrawing();
    }

    CloseWindow();
}