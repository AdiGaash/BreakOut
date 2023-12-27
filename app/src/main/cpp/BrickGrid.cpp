//
// Created by adiga on 19/12/2023.
//

#include "BrickGrid.h"




void BrickGrid::CreateAllBrickPositions(int rows, int columns, float startX, float startY, float brickWidth, float brickHeight, float rowSpacing, float columnSpacing)
{
    bricks.clear();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j) {
            float x = startX + j * (brickWidth + columnSpacing);
            float y = startY + i * (brickHeight + rowSpacing);

            int color = i % 3 + 1; // so we will have different colors and hit points
            int uid = i*columns+j;

            Brick brick(x, y, brickWidth, brickHeight, color, uid);
            bricks.push_back(brick);
        }
    }
}

Brick& BrickGrid::GetBrick(int index) {
    return bricks[index];
}

// Access the entire vector of bricks
std::vector<Brick>& BrickGrid::GetBricks(){
    return bricks;
}




