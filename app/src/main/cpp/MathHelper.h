//
// Created by adiga on 18/12/2023.
//

#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <iostream>
#include <random>

class MathHelper {
public:

    static float Clamp(float value, float min, float max);

    static int RandomNum(int minNum, int maxNum);
};

#endif // MATH_HELPER_H
