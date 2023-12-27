//
// Created by adiga on 16/12/2023.
//


#include "Ball.h"



Ball::Ball(float posX, float posY):speed(6.5), radSize(25), directionY(1.0), speedModifier(0.4), startPosX(500),startPosY(500), maxSpeed(15)
{
    Reset();
}

void Ball::Reset()
{
    speed = 6.5;
    x = startPosX;
    y = startPosY;
    directionY = 1.0;
    chooseRandomXDirection();
}

void Ball::Update(float paddleX)
{
    eventByBall = BallDidNotInteract;

    x += (directionX * speed);
    y += (directionY * speed);

    HandleWallCollisions();

    // paddle full check is done only if it collided from above
    if (y + radSize > paddleTop) {
        HandlePaddleCollision(paddleX);
    }

    HandleBricksCollision();

    BallEvent ballEvent{static_cast<EventByBall>(eventByBall)};
    for (auto& listener : ballEventListeners)
    {
        listener->OnEvent(ballEvent);
    }

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

// get the grid to be available to Ball to check for collision
void Ball::SetBrickGrid(BrickGrid& brickGrid) {
    this->brickGrid = &brickGrid;
}

bool Ball::isCollisionWithRectangle(float rectX, float rectY, float rectWidth, float rectHeight)
{

    // TODO: test this,
    // TODO: make a quicker distance test between centers?

    float closestX = std::max(rectX - rectWidth/2, std::min(x, rectX + rectWidth/2));
    float closestY = std::max(y - rectHeight/2, std::min(y, y + rectHeight/2));

    // Calculate the distance between the circle's center and the closest point on the rectangle
    float distanceX = x - closestX;
    float distanceY = y - closestY;

    // Use Pythagoras theorem to calculate the distance between the circle's center and the closest point
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    // Check if the distance is less than the radius of the circle
    return distance < radSize;
};

// Private function to handle collisions with walls
void Ball::HandleWallCollisions() {

    if (x-radSize <= 0.0) {
        // Reverse the directionX to bounce off
        directionX = -directionX;

        // Make sure the Ball is within bounds
        x = radSize;
        eventByBall = BounceFromWallEvent;
    }
    else if (x+radSize >= 1000) {
        // Reverse the directionX to bounce off
        directionX = -directionX;

        // Make sure the Ball is within bounds
        x = 1000-radSize;
        eventByBall = BounceFromWallEvent;
    }
    else if (y+radSize <= 0.0) {
        // Reverse the directionX to bounce off
        directionY = -directionY;
        // Make sure the Ball is within bounds
        y= radSize;
        eventByBall = BounceFromWallEvent;
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

        // basic Ball bouncing from paddle
        directionY = -directionY;
        y = paddleTop-radSize;

        // bouncing of x based on where on the paddle the Ball hit
        float relativeCollisionPoint = (x - paddleLeft) / paddleWidth;
        float scaledRelativeCollisionPoint = 2 * relativeCollisionPoint - 1;
        directionX += scaledRelativeCollisionPoint;

        eventByBall = BounceFromPaddleEvent;
    }

}
void Ball::AddCollisionEventListener(EventListener<CollisionEvent>* listener) {
    collisionEventListeners.push_back(listener);
}

void Ball::AddBallOutEventListener(EventListener<BallEvent>* listener) {
    ballEventListeners.push_back(listener);
}



void Ball::HandleBricksCollision() {

    auto& bricks = brickGrid->GetBricks();
    int totalBricks = static_cast<int>(bricks.size());

    for (int index = totalBricks - 1; index >= 0; --index) {
        if (IsCollide(bricks[index]))
        {
            BounceFromBrick(bricks[index]);
            speed += speedModifier;
            if (speed > maxSpeed) speed = maxSpeed;
            bricks[index].hitPoints--;
            CollisionEvent collisionEvent{ bricks[index] };

            for (auto& listener : collisionEventListeners) {
                listener->OnEvent(collisionEvent);
            }

            return;
        }
    }
}

void Ball::HandleBallOut()
{
    eventByBall = BallOutEvent;
    Reset();
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
