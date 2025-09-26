#include "Laser.hpp" 
#include "Settings.hpp"
#include <raylib.h>

Laser::Laser(Vector2 position, float speed)
    : position_(position)
    , speed_(speed)
    , active_(true)
{ }

void Laser::Draw() const
{
    if (active_)
        DrawCircle(position_.x, position_.y, laserRadius, Settings::playerColor);
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
