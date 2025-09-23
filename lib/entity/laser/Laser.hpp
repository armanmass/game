#pragma once
#include <raylib.h>

class Laser
{
public:
static constexpr int laserWidth{ 4 };
static constexpr int laserHeight{ 15 };
public:
    Laser(Vector2 position, float speed);
    void Update();
    void Draw() const;
    bool onScreen();
    bool isActive() { return active_; }
private:
    Vector2 position_{};
    float speed_{};
    bool active_{};
};
