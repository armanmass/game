#include "Game.hpp"
#include "entity/Obstacle/Obstacle.hpp"
#include <raylib.h>
#include <print>

Game::Game()
{ 
    CreateObstacles(); 
    CreateAliens();
    mysteryShip.Spawn();
}

Game::~Game()
{
    Alien::unloadImages();
}

void Game::Draw()
{
    spaceship.Draw();
    mysteryShip.Draw();
    for (const auto& laser : spaceship.getLasers())
        laser.Draw();
    for (const auto& obstacle : obstacles_)
        obstacle.Draw();
    for (const auto& alien : aliens_)
        alien.Draw();
    for (const auto& laser : alienLasers_)
        laser.Draw();
}

void Game::Update()
{
    if (GetTime()-mysteryShip.getLastSpawned() > mysteryShip.getSpawnInterval())
    {
        mysteryShip.Spawn();
        mysteryShip.updateLastSpawed();
        mysteryShip.newSpawnInterval();
    }
    mysteryShip.Update();

    for (auto& laser : spaceship.getLasers())
        laser.Update();
    MoveAliens();
    AlienShootLaser();
    for (auto& laser : alienLasers_)
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

    for (auto it = alienLasers_.begin(); it != alienLasers_.end();)
    {
        if (!it->isActive())
            it = alienLasers_.erase(it);
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

void Game::CreateAliens()
{
    for (int row{}; row < rowsOfAliens; ++row)
    {
        for (int col{}; col < colsOfAliens; ++col)
        {
            float xPos = alienStartXOffset + col * alienCellSize;
            float yPos = alienStartYOffset + row * alienCellSize;
            aliens_.emplace_back(col&1, Vector2{xPos, yPos});
        }
    }
}

void Game::MoveAliens()
{
    for (auto& alien : aliens_)
    {
        if ((alien.getPos().x < 0) || (alien.getPos().x + Alien::getImages()[alien.getType()].width > GetScreenWidth()))
        {
            aliensDirection_ *= -1.0f;
            MoveDownAliens();
            break;
        }
    }

    for (auto& alien : aliens_)
        alien.Update(aliensDirection_);
}

void Game::MoveDownAliens()
{
    for (auto& alien : aliens_)
        alien.getPos().y += alienMoveDown;
}

void Game::AlienShootLaser()
{
    if (GetTime()-alienLastFired_ >= alienFireInterval)
    {
        size_t randomIndex = GetRandomValue(0, aliens_.size()-1);
        auto& alien = aliens_[randomIndex];
        auto alienXCenter = Alien::getImages()[alien.getType()].width / 2;
        auto alienYBottom = Alien::getImages()[alien.getType()].height;
        auto alienLaserXStart = alien.getPos().x + alienXCenter;
        auto alienLaserYStart = alien.getPos().y + alienYBottom;
        alienLasers_.emplace_back(Vector2{alienLaserXStart, alienLaserYStart}, 
                                Laser::laserVertSpeed);
        alienLastFired_ = GetTime();
    }
}