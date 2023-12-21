//
// Created by adiga on 16/12/2023.
//
#include "MathHelper.h"
#include "Paddle.h"

Paddle::Paddle()
        : x(500), y(1100), width(250), height(40) {

}

Paddle::~Paddle() {

}

void Paddle::Update(float moveXRequest)
{

    x = MathHelper::clamp(x += moveXRequest,0, 1000-width/2);

}

float Paddle::GetX() const {
    return x;
}

float Paddle::GetY() const {
    return y;
}

float Paddle::GetWidth() const {
    return width;
}

float Paddle::GetHeight() const {
    return height;
}