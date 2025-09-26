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
    Rectangle getHitbox();
    auto& getLasers() { return lasers_; };
    void takeDamage(int damage);
    int getHP() { return hitpoints_; }
    void Reset();
private:
    static constexpr float spaceshipHorizSpeed{ 7.0f };
    static constexpr double laserFireCooldown{ 0.35 };
    int hitpoints_{ 3 };

    Texture2D image_;
    Vector2 position_;

    double laserLastFiredTime_{};
    std::vector<Laser> lasers_{};
};