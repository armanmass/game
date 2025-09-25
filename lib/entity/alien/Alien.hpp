#pragma once
#include <raylib.h>

class Alien
{
public:
    Alien(int type, Vector2 position);
    void Update();
    void Draw() const;

    auto getImage() { return image_; }
    auto getType() { return type_; }
    auto getPos() { return position_; }
private:
    Texture2D image_;
    Vector2 position_;
    int type_;
};
