#pragma once
#include "entity/spaceship/Spaceship.hpp"
#include "entity/Obstacle/Obstacle.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    void DeleteInactive();
private:
    void CreateObstacles();
    Spaceship spaceship{};
    std::vector<Obstacle> obstacles_;
};