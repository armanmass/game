#include "Laser.hpp" 
#include <raylib.h>

Laser::Laser(Vector2 position, float speed)
    : position_(position)
    , speed_(speed)
    , active_(true)
{ }

void Laser::Draw()
{
    static constexpr int laserWidth{ 4 };
    static constexpr int laserHeight{ 15 };
    static constexpr Color laserColorCyan{ 0, 255, 255, 255 };
    if (active_)
        DrawRectangle(position_.x, position_.y, laserWidth, laserHeight, laserColorCyan);
}

void Laser::Update()
{
    position_.y += speed_;
    if (active_)
    {
        if (position_.y > GetScreenHeight() || position_.y < 0)
            active_ = false;
    }
}
