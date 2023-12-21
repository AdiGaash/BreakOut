//
// Created by adiga on 19/12/2023.
//

#include "Brick.h"


Brick::Brick(float posX, float posY, float width, float height, int brickColor, int brickUID)
        : x(posX), y(posY), color(brickColor), uid(brickUID), minX(posX-width/2),
        minY(posY-height/2), maxX(posX+width/2), maxY(posY+height/2), giveScore(brickColor),hitPoints(brickColor){

}