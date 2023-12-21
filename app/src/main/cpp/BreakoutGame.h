//
// Created by adiga on 16/12/2023.
//

#ifndef BREAKOUTGAME_H
#define BREAKOUTGAME_H

#pragma once


#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "BrickGrid.h"
#include <vector>

#include "EventListener.h"




class BreakoutGame : public EventListener<CollisionEvent>, public EventListener<BallOutEvent>{
public:
    BreakoutGame();
    ~BreakoutGame();


    void OnEvent(CollisionEvent& event) override;
    void OnEvent(BallOutEvent& event) override;


    const Paddle& GetPaddle() const;
    BrickGrid& GetBrickGrid();
    void Init();


    int Score;
    int life;
    int brickToRemoveUID;
    Ball ball;

    // Other game-related methods

private:

    int level;
    Paddle paddle;
    BrickGrid brickGrid;
    bool ballOutEventListenerAdded = false;
    bool collisionEventListenerAdded = false;
    void NewLevel();

};


#endif // BREAKOUTGAME_H