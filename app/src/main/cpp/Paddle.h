//
// Created by adiga on 16/12/2023.
//


#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H
#include "MathHelper.h"


class Paddle {
public:
    Paddle();

    ~Paddle();

    void Update(float moveXRequest);

    float GetX() const;
    float GetY() const;
    float GetWidth() const;
    float GetHeight() const;

private:
    float x;
    float y;
    float width;
    float height;
};

#endif //BREAKOUT_PADDLE_H
