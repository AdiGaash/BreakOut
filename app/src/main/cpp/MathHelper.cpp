//
// Created by adiga on 18/12/2023.
//



#include "MathHelper.h"

float MathHelper::clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}


