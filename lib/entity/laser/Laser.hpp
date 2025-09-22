#pragma once
#include <raylib.h>

class Laser
{
public:
    Laser(Vector2 position, float speed);
    void Update();
    void Draw();
    bool onScreen();
private:
    Vector2 position_{};
    float speed_{};
    bool active_{};
};
