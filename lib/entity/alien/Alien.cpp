#include "Alien.hpp"
#include <Functions.hpp>
#include <raylib.h>
#include <print>
#include <string>

Alien::Alien(int type, Vector2 position)
    : type_(type)
    , position_(position)
{
    std::println("Creating Alien with type: {}", type_);
    std::string alienPath{"assets/aliens/"};
    switch (type)
    {
    case 1:
        alienPath += "prod";
        break;
    case 2:
        alienPath += "sean";
        break;
    default:
        alienPath += "prod";
        break;
    }
    alienPath += "64.png";
    image_ = LoadTexture(alienPath.c_str());
}

void Alien::Draw() const
{
    DrawTextureV(image_, position_, WHITE);
}
