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
#include "Events.h"
#include "EventListener.h"




class BreakoutGame : public EventListener<CollisionEvent>, public EventListener<BallEvent>{
public:
    BreakoutGame();
    ~BreakoutGame();


    void OnEvent(CollisionEvent& event) override;
    void OnEvent(BallEvent& event) override;

    void Update(float paddleX);
    const Paddle& GetPaddle() const;
    BrickGrid& GetBrickGrid();
    void Init();

    int Score;
    int Life;
    int BrickToRemove;
    Ball Ball;
    int SoundFX;
    // Other game-related methods

private:

    int brickRemoveCounter;
    int level;
    Paddle paddle;
    BrickGrid brickGrid;
    bool ballOutEventListenerAdded = false;
    bool collisionEventListenerAdded = false;
    void NewLevel();

    void RemoveCollidedBrick(const Brick &collidedBrick);
};


#endif // BREAKOUTGAME_H