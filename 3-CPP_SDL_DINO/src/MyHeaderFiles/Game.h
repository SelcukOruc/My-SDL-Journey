#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <include/SDL.h>
#include "memory"
using namespace std;

class Game
{
private:
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool _isRunning = false;
    void Start();
    void UpdateEvent(const SDL_Event &event);
    void Update();
    void OnAppQuit();
    bool IsRunning() { return _isRunning; }
};

#endif