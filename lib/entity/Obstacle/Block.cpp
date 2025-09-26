#include "Block.hpp"
#include "Settings.hpp"
#include <raylib.h>

Block::Block(Vector2 position)
    : position_(position)
{ }

void Block::Draw() const
{
    DrawRectangle(position_.x, position_.y, 3, 3, Settings::playerColor);
}

Rectangle Block::getHitbox()
{
    return {position_.x, position_.y, blockThickness, blockThickness};
}