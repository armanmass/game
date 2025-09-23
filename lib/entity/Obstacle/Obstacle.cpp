#include "Obstacle.hpp"
#include <raylib.h>

Obstacle::Obstacle(Vector2 position)
    : position_(position)
{ 
    for (size_t row{}; row < grid.size(); ++row)
    {
        for (size_t col{}; col < grid[0].size(); ++col)
        {
            if (!grid[row][col]) continue;
            float xPos = position_.x + col * 3;
            float yPos = position_.y + row * 3;
            blocks.emplace_back(Vector2{xPos, yPos});
        }
    }
}

void Obstacle::Draw() const
{
     for (const auto& block : blocks)
        block.Draw();
}