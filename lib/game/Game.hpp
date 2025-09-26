#pragma once
#include "entity/laser/Laser.hpp"
#include "entity/spaceship/Spaceship.hpp"
#include "entity/Obstacle/Obstacle.hpp"
#include "entity/alien/Alien.hpp"
#include "entity/mystery_enemy/MysteryEnemy.hpp"
#include <cstddef>

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool isRunning() { return running_; }
    int getScore() { return score_; }
    int getLives() { return spaceship.getHP(); }
private:
    void DeleteInactive();
    void CreateObstacles();
    void CreateAliens();
    void MoveAliens();
    void MoveDownAliens();
    void AlienShootLaser();
    void CheckForCollisions();
    void GameOver();
    void Reset();
    void InitGame();

    static constexpr size_t rowsOfAliens{ 5 };
    static constexpr size_t colsOfAliens{ 9 };
    static constexpr int scorePerAlien{ 1000 };
    static constexpr float alienStartXOffset{ 50.0f };
    static constexpr float alienStartYOffset{ 200.0f };
    static constexpr float alienCellSize{ 72.0f };
    static constexpr float alienMoveDown{ 5.0f };
    static constexpr float alienFireInterval{ 0.35f };
    float alienLastFired_{};

    MysteryEnemy mysteryShip{};
    Spaceship spaceship{};
    std::vector<Obstacle> obstacles_;
    std::vector<Alien> aliens_;
    std::vector<Laser> alienLasers_;
    float aliensDirection_{ 1.5f };
    int score_{};
    bool running_{ true };
};