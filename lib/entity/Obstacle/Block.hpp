#pragma once
#include <raylib.h>

class Block
{
public:
    Block(Vector2 position);
    void Draw() const;
private:
    static constexpr Color blockColor{ 243, 216, 63, 255 };
    Vector2 position_;
};