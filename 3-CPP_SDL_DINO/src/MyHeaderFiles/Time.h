#ifndef TIME_H
#define TIME_H

#include "MyHeaderFiles/Game.h"

struct Time
{
private:
    static Uint32 currentTime;
    static Uint32 lastTime;
    static float _deltaTime;

public:
    static float deltaTime();
};

#endif