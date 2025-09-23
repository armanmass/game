#include "Game.hpp"
#include <raylib.h>
#include <print>

Game::Game(){}

Game::~Game(){}

void Game::Draw()
{
    spaceship.Draw();
    for (const auto& laser : spaceship.getLasers())
        laser.Draw();
}

void Game::Update()
{

    for (auto& laser : spaceship.getLasers())
        laser.Update();
    DeleteInactive();
}
void Game::HandleInput()
{
    if (IsKeyDown(KEY_A))
        spaceship.MoveLeft();
    else if (IsKeyDown(KEY_D))
        spaceship.MoveRight();
    else if (IsKeyDown(KEY_SPACE))
        spaceship.FireLaser();
}

void Game::DeleteInactive()
{
    auto& lasers = spaceship.getLasers();
    for (auto it = lasers.begin(); it != lasers.end();)
    {
        if (!it->isActive())
            it = lasers.erase(it);
        else
            ++it;
    }
}