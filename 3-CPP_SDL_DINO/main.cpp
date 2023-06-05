#include "MyHeaderFiles/Game.h"
#include "MyHeaderFiles/Time.h"
#include "MyHeaderFiles/Config.h"
#include "src/include/SDL_ttf.h"
#include "MyHeaderFiles/Colors.h"
std::unique_ptr<Game> game = nullptr;

void Init(const char *_title, int h, int w, bool _isfullscreen)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        exit(-1);

    if (TTF_Init() < 0)
    {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
    }

    game->window = SDL_CreateWindow(_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, _isfullscreen);
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);
    game->_isRunning = true;
}

int main(int argc, char **argv)
{
    game = std::make_unique<Game>();
    Init("Selam", SCREEN_HEIGHT, SCREEN_WIDTH, false);
    game->Start();
    CONFIG::ResizeHasCollidedArray();
    while (game->IsRunning())
    {
        SDL_Event event;

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game->_isRunning = false;
                break;
            }
            game->UpdateEvent(event);
        }
        // Background color.
        SDL_SetRenderDrawColor(game->renderer, Colors::Gray.r, Colors::Gray.g, Colors::Gray.b, 255);
        SDL_RenderClear(game->renderer);
        game->Update();
        SDL_RenderPresent(game->renderer);
    }

    game->OnAppQuit();

    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    SDL_Quit();

    return 0;
}