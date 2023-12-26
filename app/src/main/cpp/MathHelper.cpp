//
// Created by adiga on 18/12/2023.
//



#include "MathHelper.h"

float MathHelper::Clamp(float value, float min, float max)
{
    return (value < min) ? min : (value > max) ? max : value;
}

int MathHelper::RandomNum(int minNum, int maxNum)
{
    std::mt19937 gen(std::random_device{}());  // Automatic seeding
    std::uniform_int_distribution<int> distribution(minNum, maxNum);
    int random_number;
    return random_number = distribution(gen);
}




