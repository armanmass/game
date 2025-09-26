#include "Spaceship.hpp"
#include <Functions.hpp>
#include <raylib.h>

Spaceship::Spaceship()
{ 
    Image image = raylib::LoadImage("assets/spaceship/sage.png");
    ImageResize(&image, image.width/5, image.height/5);
    image_ = LoadTextureFromImage(image);
    UnloadImage(image);

    position_.x = (GetScreenWidth()-image_.width)/2.0f;
    position_.y = (GetScreenHeight()-image_.height);

    laserLastFiredTime = 0.0;
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
    position_.x = std::max(position_.x, 0.0f);
}

void Spaceship::MoveRight()
{
    position_.x += spaceshipHorizSpeed;
    position_.x = std::min(position_.x, static_cast<float>(GetScreenWidth())-image_.width);
}

void Spaceship::FireLaser()
{
    if (GetTime() - laserLastFiredTime >= laserFireCooldown)
    {
        Vector2 laserStartPos {position_.x + image_.width/2.0f - Laser::laserWidth/2.0f, position_.y};
        lasers.emplace_back(laserStartPos, -Laser::laserVertSpeed);
        laserLastFiredTime = GetTime();
    }
}
