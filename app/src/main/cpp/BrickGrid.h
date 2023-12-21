//
// Created by adiga on 19/12/2023.
//

#ifndef BREAKOUT_BRICKGRID_H
#define BREAKOUT_BRICKGRID_H

#include <vector>
#include "Brick.h"

class BrickGrid {
private:
    std::vector<std::vector<Brick>> bricks; // Make bricks private

public:
    // Function to create brick positions
    void CreateAllBrickPositions(int rows, int columns, float startX, float startY, float brickWidth, float brickHeight, float rowSpacing, float columnSpacing);

    // Function to get the bricks
     std::vector<std::vector<Brick>>& GetBricks();
};


#endif //BREAKOUT_BRICKGRID_H
