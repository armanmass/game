#pragma once
#include <raylib.h>

class Block
{
public:
    Block(Vector2 position);
    void Draw() const;
private:
    Vector2 position_;
};