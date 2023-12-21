//
// Created by adiga on 20/12/2023.
//

#ifndef BREAKOUT_EVENTS_H
#define BREAKOUT_EVENTS_H

#include "Brick.h"

// CollisionEvent
struct CollisionEvent {
     Brick collidedBrick;
    // You can add more information related to the collision if needed
};

// BallOutEvent
struct BallOutEvent {
    // You can add more information related to the event if needed
};

#endif //BREAKOUT_EVENTS_H
