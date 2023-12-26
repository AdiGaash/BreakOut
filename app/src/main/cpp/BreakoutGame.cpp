//
// Created by adiga on 16/12/2023.
//
#include <android/log.h>

#include "BreakoutGame.h"

BreakoutGame::BreakoutGame()
{
    // this is just in case we will have more then one instance for some strange reason
    if (!ballOutEventListenerAdded) {
        Ball.AddBallOutEventListener(this);
        ballOutEventListenerAdded = true;
    }

    if (!collisionEventListenerAdded) {
        Ball.AddCollisionEventListener(this);
        collisionEventListenerAdded = true;
    }

    Init();
}
BreakoutGame::~BreakoutGame() {

}


const Paddle& BreakoutGame::GetPaddle() const
{
    return paddle;
}
 BrickGrid& BreakoutGame::GetBrickGrid()
{
    return brickGrid;
}

void BreakoutGame::OnEvent(CollisionEvent& event)
{
    __android_log_print(ANDROID_LOG_DEBUG, "BreakoutGameCPP", "BrickCollide!");
    Brick collidedBrick = (event.collidedBrick);

    collidedBrick.hitPoints--;
    if(collidedBrick.hitPoints<1)
    {
        Score += collidedBrick.giveScore;
        // need to remove brick from array;
        BrickToRemove = collidedBrick.uid;
        SoundFX = 4;

        // Find and remove the specific brick from the array
        for (auto& row : brickGrid.GetBricks()) {
            auto it = std::find_if(row.begin(), row.end(), [uid = BrickToRemove](const Brick& brick) {
                return brick.uid == uid;
            });

            if (it != row.end()) {
                row.erase(it);
                break;
            }
        }

        if(brickGrid.GetBricks().empty())
        {
            SoundFX = 7;
            NewLevel();
        }
    }
    else
    {
        SoundFX = 6;
    }






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
    brickGrid.CreateAllBrickPositions(level+4, 10, 60.0, 80.0, 104.0, 39.0, 3.0, 3.0);
}
void BreakoutGame::Init() {
    // reset score
    Score = 0;
    BrickToRemove = -1;
    Life = 3;
    level = 0;



    NewLevel();

}

void BreakoutGame::Update(float paddleX)
{

    SoundFX = -1;
    Ball.Update(paddleX);

}











