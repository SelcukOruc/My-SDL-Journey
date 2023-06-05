#include "MyHeaderFiles/Time.h"

Uint32 Time::currentTime = 0;
Uint32 Time::lastTime = 0;
float Time::_deltaTime = 0;

float Time::deltaTime()
{
    lastTime = currentTime;
    currentTime = SDL_GetPerformanceCounter();

    _deltaTime = (double)((currentTime - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());
    // cout << to_string(_deltaTime) << endl;
    return _deltaTime;
}