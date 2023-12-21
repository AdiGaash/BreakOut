//
// Created by adiga on 20/12/2023.
//

#ifndef EVENTS_H
#define EVENTS_H

#include "Brick.h"

// CollisionEvent
struct CollisionEvent {
     Brick collidedBrick;
};

// Enum declaration
enum EventByBall {
    BallDidNotInteract,
    BallOutEvent,
    BounceFromPaddleEvent,
    BounceFromWallEvent,
    BounceFromBrickEvent
};

// BallOutEvent struct
struct BallEvent {
    EventByBall event;
};

#endif //EVENTS_H
