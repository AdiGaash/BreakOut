//
// Created by adiga on 19/12/2023.
//

#ifndef BREAKOUT_BRICKGRID_H
#define BREAKOUT_BRICKGRID_H

#include <vector>
#include "Brick.h"

class BrickGrid {


public:

    // Function to create brick positions
    void CreateAllBrickPositions(int rows, int columns, float startX, float startY, float brickWidth,
                            float brickHeight, float rowSpacing, float columnSpacing);

    // Function to get the bricks
    // Access elements using 1D index

    // Access the entire vector of bricks
    std::vector<Brick>& GetBricks();

private:
    std::vector<Brick> bricks;
};

#endif //BREAKOUT_BRICKGRID_H
