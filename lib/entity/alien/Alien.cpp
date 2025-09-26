#include "Alien.hpp"
#include <Functions.hpp>
#include <raylib.h>
#include <print>
#include <string>

Texture2D Alien::alienImages_[3]{};

Alien::Alien(int type, Vector2 position)
    : type_(type)
    , position_(position)
{
    std::println("Creating Alien with type: {}", type_);
    std::string alienPath{"assets/aliens/"};
    switch (type)
    {
    case 0:
        alienPath += "prod";
        break;
    case 1:
        alienPath += "sean";
        break;
    default:
        alienPath += "prod";
        break;
    }
    alienPath += "64.png";
    if (alienImages_[type_].id == 0)
        alienImages_[type_] = LoadTexture(alienPath.c_str());
}

void Alien::Update(float direction)
{
    position_.x += direction;
}


void Alien::Draw() const
{
    DrawTextureV(alienImages_[type_], position_, WHITE);
}

void Alien::unloadImages()
{
    for(const auto& image : alienImages_)
        UnloadTexture(image);
}

Rectangle Alien::getHitbox()
{
    return {position_.x, position_.y, 
            static_cast<float>(alienImages_[type_].width), 
            static_cast<float>(alienImages_[type_].height)};
}