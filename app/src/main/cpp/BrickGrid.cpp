//
// Created by adiga on 19/12/2023.
//

#include "BrickGrid.h"



void BrickGrid::CreateAllBrickPositions(int rows, int columns, float startX, float startY, float brickWidth, float brickHeight, float rowSpacing, float columnSpacing)
{
    bricks.clear(); // Clear any existing data

    for (int i = 0; i < rows; ++i)
    {
        std::vector<Brick> row;

        for (int j = 0; j < columns; ++j)
        {
            float x = startX + j * (brickWidth + columnSpacing);
            float y = startY + i * (brickHeight + rowSpacing);

            int color =  i % 3 +1; // so we will have different colors and hit points
            int uid = i * columns + j + 1;

            Brick brick(x, y, brickWidth, brickHeight, color, uid);
            row.push_back(brick);
        }

        bricks.push_back(row);
    }
}

 std::vector<std::vector<Brick>>& BrickGrid::GetBricks()
{
    return bricks;
}