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


// this ball events for SFX and game logic...
// This is temporary
// TODO: fix object design and better not use event listener pattern.

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
    EventByBall ballEvent;
};

#endif //EVENTS_H
