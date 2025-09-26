#include "MysteryEnemy.hpp"
#include <raylib.h>
#include "Settings.hpp"

MysteryEnemy::MysteryEnemy()
{
    image_ = LoadTexture("assets/mystery/mystery.png");
    newSpawnInterval();
}

MysteryEnemy::~MysteryEnemy()
{
    UnloadTexture(image_);
}

void MysteryEnemy::Spawn()
{
    position_.y = startY + Settings::vertOffset;
    int side = GetRandomValue(0, 1);

    if (side)
    {
        position_.x = Settings::horizOffset;
        speed = 3.0f;
    }
    else
    {
        position_.x = GetScreenWidth() - image_.width - Settings::horizOffset;
        speed = -3.0f;
    }
    alive_ = true;
}

void MysteryEnemy::Update()
{
    if (alive_)
    {
        position_.x += speed;
        if (position_.x < Settings::horizOffset || position_.x > GetScreenWidth()-Settings::horizOffset-image_.width)
        {
            alive_ = false;
        }
    }
}

void MysteryEnemy::Draw() const
{
    if (alive_)
        DrawTextureV(image_, position_, WHITE);
}

Rectangle MysteryEnemy::getHitbox()
{
    if (alive_)
        return {position_.x, position_.y, static_cast<float>(image_.width), static_cast<float>(image_.height)};
    return {};
}