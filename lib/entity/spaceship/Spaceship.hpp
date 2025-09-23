#pragma once
#include <raylib.h>
#include <vector>
#include "entity/laser/Laser.hpp"


class Spaceship
{
public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    auto& getLasers() { return lasers; };
private:
    static constexpr float spaceshipHorizSpeed{ 7.0f };
    static constexpr float laserVertSpeed{ -6.0f };
    static constexpr double laserFireCooldown{ 0.35 };

    Texture2D image_;
    Vector2 position_;

    double laserLastFiredTime{};
    std::vector<Laser> lasers{};
};