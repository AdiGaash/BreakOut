//
// Created by adiga on 20/12/2023.
//

#ifndef BREAKOUT_EVENTLISTENER_H
#define BREAKOUT_EVENTLISTENER_H
#pragma once

#include <functional>

template<typename EventType>
class EventListener {
public:
    virtual void OnEvent(EventType& event) = 0;
};


#endif //BREAKOUT_EVENTLISTENER_H
