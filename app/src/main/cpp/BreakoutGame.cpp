//
// Created by adiga on 16/12/2023.
//
#include <android/log.h>

#include "BreakoutGame.h"

BreakoutGame::BreakoutGame()
{
    // this is just in case we will have more then one instance for some strange reason
    if (!ballOutEventListenerAdded) {
        ball.AddBallOutEventListener(this);
        ballOutEventListenerAdded = true;
    }

    if (!collisionEventListenerAdded) {
        ball.AddCollisionEventListener(this);
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
        brickToRemoveUID = collidedBrick.uid;

        // Find and remove the specific brick from the array
        for (auto& row : brickGrid.GetBricks()) {
            auto it = std::find_if(row.begin(), row.end(), [uid = brickToRemoveUID](const Brick& brick) {
                return brick.uid == uid;
            });

            if (it != row.end()) {

                row.erase(it);
                break;
            }
        }
    }

    if(brickGrid.GetBricks().empty())
    {
        // send you win event!
    }



}
void BreakoutGame::OnEvent(BallOutEvent& event) {


    this->life--;
    if (this->life < 0)
    {
        return;
    }



}

void BreakoutGame::NewLevel()
{
    ball.Reset();
    // create bricks
    brickGrid.CreateAllBrickPositions(level+4, 10, 60.0, 75.0, 104.0, 39.0, 3.0, 3.0);
}
void BreakoutGame::Init() {
    // reset score
    Score = 0;
    brickToRemoveUID = -1;
    life = 3;
    level = 0;


    NewLevel();

}











