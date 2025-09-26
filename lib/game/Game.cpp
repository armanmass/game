#include "Game.hpp"
#include "entity/Obstacle/Obstacle.hpp"
#include <raylib.h>
#include "Settings.hpp"

Game::Game()
{ 
    InitGame();
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
    if (isRunning())
    {
        if (GetTime()-mysteryShip.getLastSpawned() > mysteryShip.getSpawnInterval())
        {
            mysteryShip.Spawn();
            mysteryShip.updateLastSpawed();
            mysteryShip.newSpawnInterval();
        }
        mysteryShip.Update();
        CheckForCollisions();
        for (auto& laser : spaceship.getLasers())
            laser.Update();
        MoveAliens();
        AlienShootLaser();
        for (auto& laser : alienLasers_)
            laser.Update();
        DeleteInactive();
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
}

void Game::HandleInput()
{
    if (isRunning())
    {
        if (IsKeyDown(KEY_A))
            spaceship.MoveLeft();
        else if (IsKeyDown(KEY_D))
            spaceship.MoveRight();
        else if (IsKeyDown(KEY_SPACE))
            spaceship.FireLaser();
    }
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
    float yPos = GetScreenHeight() - 200.0f - Settings::vertOffset;
    
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
        if ((alien.getPos().x <= Settings::horizOffset) || (alien.getPos().x + Alien::getImages()[alien.getType()].width >= GetScreenWidth()-Settings::horizOffset))
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

void Game::CheckForCollisions()
{
    for (auto& laser : spaceship.getLasers())
    {
        auto it = aliens_.begin();
        for (; it != aliens_.end();)
        {
            if (CheckCollisionCircleRec(laser.getPos(), Laser::laserRadius, it->getHitbox()))
            {
                score_ += scorePerAlien*(it->getType()+1);
                it = aliens_.erase(it);
                laser.deactivate();
            }
            else
            {
                ++it;
            }
        }

        for (auto& obstacle : obstacles_)
        {
            auto it = obstacle.getBlocks().begin();
            for (; it != obstacle.getBlocks().end();)
            {
                if (CheckCollisionCircleRec(laser.getPos(), Laser::laserRadius, it->getHitbox()))
                {
                    it = obstacle.getBlocks().erase(it);
                    laser.deactivate();
                }
                else
                {
                    ++it;
                }
            }
        }

        if (CheckCollisionCircleRec(laser.getPos(), Laser::laserRadius, mysteryShip.getHitbox()))
        {
            score_ += 5*scorePerAlien;
            mysteryShip.unalive();
            laser.deactivate();
        }
    }

    for (auto& laser : alienLasers_)
    {
        if (CheckCollisionCircleRec(laser.getPos(), Laser::laserRadius, spaceship.getHitbox()))
        {
            spaceship.takeDamage(1);
            if (spaceship.getHP() == 0)
                GameOver();
            laser.deactivate();
        }

        for (auto& obstacle : obstacles_)
        {
            auto it = obstacle.getBlocks().begin();
            for (; it != obstacle.getBlocks().end();)
            {
                if (CheckCollisionCircleRec(laser.getPos(), Laser::laserRadius, it->getHitbox()))
                {
                    it = obstacle.getBlocks().erase(it);
                    laser.deactivate();
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    for (auto& alien : aliens_)
    {
        for (auto& obstacle : obstacles_)
        {
            auto it = obstacle.getBlocks().begin();
            for (; it != obstacle.getBlocks().end();)
            {
                if (CheckCollisionRecs(alien.getHitbox(), it->getHitbox()))
                {
                    it = obstacle.getBlocks().erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(alien.getHitbox(), spaceship.getHitbox()))
            GameOver();
    }
}

void Game::GameOver()
{
    running_ = false;
}

void Game::InitGame()
{
    CreateObstacles(); 
    CreateAliens();
    mysteryShip.Spawn();
    alienLastFired_ = 0.0f;
    aliensDirection_ = 1.5f;
    score_ = 0;
    running_ = true;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens_.clear();
    alienLasers_.clear();
    obstacles_.clear();
}