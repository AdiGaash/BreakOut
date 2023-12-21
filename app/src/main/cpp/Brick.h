//
// Created by adiga on 19/12/2023.
//

#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H


class Brick {
public:
    float x;
    float y;
    int color;  // Assuming hit-points / strength / start color of brick is an integer representation
    int uid;// Assuming UID is an integer
    float minX;
    float minY;
    float maxX;
    float maxY;
    int giveScore;
    int hitPoints;

    // Constructor that accepts all parameters
    Brick(float posX, float posY, float width, float height, int brickColor, int brickUID);


};

#endif //BREAKOUT_BRICK_H
