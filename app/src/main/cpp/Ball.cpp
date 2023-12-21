//
// Created by adiga on 16/12/2023.
//


#include "Ball.h"
#include <android/log.h>


Ball::Ball(float posX, float posY):speed(5.0), radSize(25), directionY(1.0), speedModifier(0.4), startPosX(500),startPosY(500)
{
    Reset();
}

void Ball::Reset()
{

    speed = 5.0;
    x = startPosX;
    y = startPosY;
    directionY = 1.0;
    chooseRandomXDirection();
}

void Ball::Update(float paddleX)
{

    x += (directionX * speed);
    y += (directionY * speed);

    HandleWallCollisions();

    // paddle full check is done only if it collided from above
    if(y+radSize > paddleTop)
    HandlePaddleCollision(paddleX);

    HandleBricksCollision();
}

// Implementation of getter functions
float Ball::GetX() const {
    return x;
}

float Ball::GetY() const {
    return y;

}
void Ball::chooseRandomXDirection()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    // Randomly set the initial directionX to -1 or 1
    directionX = (std::rand() % 2 == 0) ? -1.0f : 1.0f;
}




void Ball::GetPaddleParameters(Paddle& paddle)
{
    float paddleHeight = paddle.GetHeight();
    float paddleY = paddle.GetY();
    paddleTop = paddleY-paddleHeight/2;
    paddleWidth = paddle.GetWidth();
}

// get the grid to be available to ball to check for collision
void Ball::SetBrickGrid(BrickGrid& brickGrid) {
    this->brickGrid = &brickGrid;
}



// Private function to handle collisions with walls
void Ball::HandleWallCollisions() {

    if (x-radSize <= 0.0) {
        // Reverse the directionX to bounce off
        directionX = -directionX;

        // Make sure the ball is within bounds
        x = radSize;
    }
    else if (x+radSize >= 1000) {
        // Reverse the directionX to bounce off
        directionX = -directionX;

        // Make sure the ball is within bounds
        x = 1000-radSize;
    }


    if (y+radSize <= 0.0) {
        // Reverse the directionX to bounce off
        directionY = -directionY;
        // Make sure the ball is within bounds
        y= radSize;
    }
    else if (y+radSize > 1200)
    {
        HandleBallOut();
    }
}



void Ball::HandlePaddleCollision(float paddleX) {

    float paddleLeft = paddleX-paddleWidth/2 ;
    float paddleRight = paddleX + paddleWidth/2;
    // no need to check collision from below paddle
    if (x+radSize >= paddleLeft && x-radSize <= paddleRight) {

        // basic ball bouncing from paddle
        directionY = -directionY;
        y = paddleTop-radSize;

        // bouncing of x based on where on the paddle the ball hit
        float relativeCollisionPoint = (x - paddleLeft) / paddleWidth;
        float scaledRelativeCollisionPoint = 2 * relativeCollisionPoint - 1;
        directionX += scaledRelativeCollisionPoint;

    }

}
void Ball::AddCollisionEventListener(EventListener<CollisionEvent>* listener) {
    collisionEventListeners.push_back(listener);
}

void Ball::AddBallOutEventListener(EventListener<BallOutEvent>* listener) {
    ballOutEventListeners.push_back(listener);
}



void Ball::HandleBricksCollision() {

    auto& bricks = brickGrid->GetBricks();

    for (auto row = bricks.rbegin(); row != bricks.rend(); ++row) {
        for (auto brick = row->begin(); brick != row->end(); ++brick) {
            if (IsCollide(*brick))
            {
                BounceFromBrick(*brick);
                speed+=speedModifier;
                CollisionEvent collisionEvent{ *brick };
                (*brick).hitPoints--;

                for (auto& listener : collisionEventListeners)
                {
                    listener->OnEvent(collisionEvent);

                }
                return;
            }
        }
    }
}

void Ball::HandleBallOut()

{
    Reset();

    BallOutEvent ballOutEvent;
    // Notify ball out event listeners
    for (auto& listener : ballOutEventListeners) {
        listener->OnEvent(ballOutEvent);
    }

}

void Ball::BounceFromBrick(const Brick& brick) {
    side near = left;
    float nearDistance = abs(brick.minX - x);
    float distance = abs(brick.maxX - x);
    if (distance < nearDistance) {
        nearDistance = distance;
        near = right;
    }
    distance = abs(brick.minY - y);
    if (distance < nearDistance) {
        nearDistance = distance;
        near = top;
    }
    distance = abs(brick.maxY - y);
    if (distance < nearDistance) {
        nearDistance = distance;
        near = bottom;
    }
    switch(near)
    {
        case left:
            x = brick.minX - radSize;
            directionX = -directionX;
            break;
        case right:
            x = brick.maxX + radSize;
            directionX = - directionX;
            break;
        case top:
            y = brick.minY - radSize;
            directionY = - directionY;
            break;
        case bottom:
            y = brick.maxY + radSize;
            directionY = - directionY;
            break;

    }
}
 bool Ball::IsCollide(const Brick& brick) {
     // Check if any of the conditions for no collision are met
     if (x + radSize < brick.minX || x - radSize > brick.maxX ||
         y + radSize < brick.minY || y - radSize > brick.maxY) {
         return false;
     }
     return true;
 }
