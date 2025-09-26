#include "Spaceship.hpp"
#include <Functions.hpp>
#include <raylib.h>
#include "Settings.hpp"

Spaceship::Spaceship()
{ 
    Image image = raylib::LoadImage("assets/spaceship/sage.png");
    ImageResize(&image, image.width/5, image.height/5);
    image_ = LoadTextureFromImage(image);
    UnloadImage(image);

    position_.x = (GetScreenWidth()-image_.width) / 2.0f;
    position_.y = (GetScreenHeight()-image_.height) - Settings::vertOffset;

    laserLastFiredTime_ = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image_);
}

void Spaceship::Draw()
{
    DrawTextureV(image_, position_, WHITE);
}

void Spaceship::MoveLeft()
{
    position_.x -= spaceshipHorizSpeed;
    position_.x = std::max(position_.x, (float)Settings::horizOffset);
}

void Spaceship::MoveRight()
{
    position_.x += spaceshipHorizSpeed;
    position_.x = std::min(position_.x, static_cast<float>(GetScreenWidth())-image_.width-Settings::horizOffset);
}

void Spaceship::FireLaser()
{
    if (GetTime() - laserLastFiredTime_ >= laserFireCooldown)
    {
        Vector2 laserStartPos {position_.x + image_.width/2.0f - Laser::laserRadius/2.0f, position_.y};
        lasers_.emplace_back(laserStartPos, -Laser::laserVertSpeed);
        laserLastFiredTime_ = GetTime();
    }
}

Rectangle Spaceship::getHitbox()
{
    return {position_.x, position_.y, static_cast<float>(image_.width), static_cast<float>(image_.height)};
}

void Spaceship::takeDamage(int damage)
{
    hitpoints_ -= damage;
}

void Spaceship::Reset()
{
    position_.x = (GetScreenWidth()-image_.width) / 2.0f;
    position_.y = (GetScreenHeight()-image_.height) - Settings::vertOffset;
    lasers_.clear();
    hitpoints_ = 3;
    laserLastFiredTime_ = 0.0f;
}