#include "Game.hpp"
#include "entity/Obstacle/Obstacle.hpp"
#include <raylib.h>
#include <print>

Game::Game()
{ CreateObstacles(); }

Game::~Game(){}

void Game::Draw()
{
    spaceship.Draw();
    for (const auto& laser : spaceship.getLasers())
        laser.Draw();
    for (const auto& obstacle : obstacles_)
        obstacle.Draw();
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

void Game::CreateObstacles()
{
    float obstacleWidth = Obstacle::grid[0].size() * 3;
    float gapSize = (GetScreenWidth() - (4.0f*obstacleWidth)) / 5.0f;
    float yPos = GetScreenHeight() - 200.0f;
    
    for (size_t i{}; i < Obstacle::numObstacles; ++i)
    {
        float xPos = (i+1)*gapSize + i*obstacleWidth;
        obstacles_.emplace_back(Vector2{xPos, yPos});
    }
}