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
    void DeleteInactive();
private:
    Spaceship spaceship{};
};