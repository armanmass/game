#include "Block.hpp"
#include <raylib.h>

Block::Block(Vector2 position)
    : position_(position)
{ }

void Block::Draw()
{
    DrawRectangle(position_.x, position_.y, 3, 3, blockColor);
}