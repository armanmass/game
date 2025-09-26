#pragma once
#include <raylib.h>

class Block
{
public:
    static constexpr int blockThickness{ 3 };
public:
    Block(Vector2 position);
    void Draw() const;
    Rectangle getHitbox();
private:
    Vector2 position_;
};