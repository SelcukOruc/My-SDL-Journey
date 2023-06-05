#ifndef RANDOM_H
#define RANDOM_H

#include "Game.h"
#include "random"
class Random
{
public:
    static int RandomNumber(int min, int max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(min, max);

        return distr(gen);
    }
};

#endif