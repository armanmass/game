#pragma once
#include "entity/spaceship/Spaceship.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
private:
    Spaceship spaceship{};
};