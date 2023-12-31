//
// Created by adiga on 16/12/2023.
//
#include <android/log.h>

#include "BreakoutGame.h"

BreakoutGame::BreakoutGame()
{
    // this is just in case we will have more then one instance for some strange reason
    if (!ballEventListenerAdded) {
        Ball.AddBallOutEventListener(this);
        ballEventListenerAdded = true;
    }

    if (!collisionEventListenerAdded) {
        Ball.AddCollisionEventListener(this);
        collisionEventListenerAdded = true;
    }

    Init();
}

BreakoutGame::~BreakoutGame()
{
    if(collisionEventListenerAdded)
        Ball.RemoveCollisionEventListener(this);

    if(ballEventListenerAdded)
        Ball.RemoveBallEventListener(this);
}


const Paddle& BreakoutGame::GetPaddle() const
{
    return paddle;
}
 BrickGrid& BreakoutGame::GetBrickGrid()
{
    return brickGrid;
}


void BreakoutGame::RemoveCollidedBrick(const Brick& collidedBrick) {
    auto& bricks = brickGrid.GetBricks();
    auto it = std::find_if(bricks.begin(), bricks.end(),
                           [uid = collidedBrick.uid](const Brick& brick) {
                               return brick.uid == uid;
                           });

    if (it != bricks.end()) {
        bricks.erase(it);
        BrickToRemove = collidedBrick.uid;
    }
}

void BreakoutGame::OnEvent(CollisionEvent& event)
{
    __android_log_print(ANDROID_LOG_DEBUG, "BreakoutGameCPP", "BrickCollide!");
    Brick collidedBrick = (event.collidedBrick);

    if (collidedBrick.hitPoints < 1)
    {
        Score += collidedBrick.giveScore;
        SoundFX = 4;

        // Remove the specific brick from the array
        RemoveCollidedBrick(collidedBrick);
    }

    if (brickGrid.GetBricks().empty())
    {
        SoundFX = 7;
        level++;
        NewLevel();
    }
    else
        SoundFX = 6;
}


void BreakoutGame::OnEvent(BallEvent& event)
{

    EventByBall ballEvent = (event.ballEvent);

    switch(ballEvent)
    {
        case BallOutEvent:
            this->Life--;
            SoundFX = 5;
            break;
        case BounceFromPaddleEvent:
            SoundFX = MathHelper::RandomNum(2,3);
            break;
        case  BounceFromWallEvent:
            SoundFX = MathHelper::RandomNum(0,1);
            break;
        case BallDidNotInteract:
            break;
        case BounceFromBrickEvent:
            break;
    }
}

void BreakoutGame::NewLevel()
{
    Ball.Reset();
    // create bricks
    brickGrid.CreateAllBrickPositions(level+4, 10, 55.0, 100.0, 104.0, 39.0, 3.0, 3.0);
}
void BreakoutGame::Init() {

    Score = 0;
    Life = 3;
    level = 0;

    NewLevel();
}

void BreakoutGame::Update(float paddleX)
{
    BrickToRemove = -1;
    SoundFX = -1;
    Ball.Update(paddleX);

}











