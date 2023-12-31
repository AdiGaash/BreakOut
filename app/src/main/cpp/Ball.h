//
// Created by adiga on 16/12/2023.
//



#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H


#include "Paddle.h"
#include "Brick.h"
#include "BrickGrid.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

#include <android/log.h>
#include "Brick.h"
#include "EventListener.h"
#include "Events.h"

class Ball {


public:


    void AddCollisionEventListener(EventListener<CollisionEvent>* listener);
    void AddBallOutEventListener(EventListener<BallEvent>* listener);
    void RemoveCollisionEventListener(EventListener<CollisionEvent>* listener);
    void RemoveBallEventListener(EventListener<BallEvent>* listener);

    Ball(float posX = 0.0f, float posY = 0.0f);




    float GetX() const;
    float GetY() const;
    void Update(float paddleX);
    void GetPaddleParameters(Paddle& paddle);
    void SetBrickGrid(BrickGrid& brickGrid);
    void Reset();




private:

    void chooseRandomXDirection();
    float speed;
    float radSize;
    float x;
    float y;
    float directionX;
    float directionY;
    float paddleTop;
    float paddleWidth;
    float speedModifier;
    float maxSpeed;
    float startPosX;
    float startPosY;
    BrickGrid* brickGrid;

    EventByBall eventByBall;
    void HandleBallOut();
    void HandleBricksCollision();
    void HandleWallCollisions();
    void HandlePaddleCollision(float paddleX);
    bool IsCollideWithBrick(const Brick& brick);
    void BounceFromBrick(const Brick& brick);
    std::vector<EventListener<CollisionEvent>*> collisionEventListeners;
    std::vector<EventListener<BallEvent>*> ballEventListeners;
    enum side
    {
        left,right,top,bottom
    };

};

#endif //BREAKOUT_BALL_H
