#include "MysteryEnemy.hpp"
#include <raylib.h>

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
    position_.y = startY;
    int side = GetRandomValue(0, 1);
    position_.x = (side != 0) * GetScreenWidth() - (side==0)*image_.width;

    if (side)
        speed = -3.0f;
    else
        speed = 3.0f;
    alive_ = true;
}

void MysteryEnemy::Update()
{
    if (alive_)
    {
        position_.x += speed;
        if (position_.x <= -image_.width || position_.x > GetScreenWidth())
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