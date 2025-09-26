#pragma once
#include <raylib.h>

class Alien
{
public:
    Alien(int type, Vector2 position);
    void Update(float direction);
    void Draw() const;

    static auto& getImages() { return alienImages_; }
    auto getType() { return type_; }
    auto& getPos() { return position_; }
    static void unloadImages();
private:
    static Texture2D alienImages_[3];
    Vector2 position_;
    int type_;
};
