#include <iostream>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <random>
#include <CUSTOM/Random.h>
#include "CUSTOM/Time.h"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

Time time;
float deltaTime;

int ObjectNumberCreated = 0;

#include "CUSTOM/Colors.h"
#include "CUSTOM/Debug.h"
#include "CUSTOM/config.h"
#include "CUSTOM/Vector2.h"
#include "CUSTOM/Input.h"
#include "CUSTOM/Transform.h"
#include "CUSTOM/Text.h"
#include "CUSTOM/Sprite.h"
#include "CUSTOM/Collision.h"
#include "CUSTOM/Button.h"
#include "CUSTOM/Game.h"

void CreateWindow()
{
    window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
}

void CreateRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

void Init()
{
    if (SDL_Init(SDL_INIT_VIDEO == -1) || TTF_Init() == -1)
    {
        exit(-1);
    }

    CreateWindow();
    CreateRenderer();
}

void GeneralEventManager(SDL_Event _event)
{
    switch (_event.type)
    {
    case SDL_QUIT:
        IsGameRunning = false;
        break;

    default:
        break;
    }
}

int main(int argc, char **argv)
{
    Init();
    SetCollisionLimit();
    Awake();
    Start();

    while (IsGameRunning)
    {
        deltaTime = time.deltaTime();

        SDL_RenderClear(renderer);

        if (SDL_PollEvent(&event))
        {
            GeneralEventManager(event);
        }
        Update();
        SDL_SetRenderDrawColor(renderer, Colors::Black.r, Colors::Black.g, Colors::Black.b, 255);
        SDL_RenderPresent(renderer);
    }

    OnApplicationQuit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}