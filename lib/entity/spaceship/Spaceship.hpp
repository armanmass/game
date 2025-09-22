#pragma once
#include <raylib.h>

class Spaceship
{
public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
private:
    Texture2D image_;
    Vector2 position_;
    static constexpr float horizontalSpeed{ 7.0f };
};