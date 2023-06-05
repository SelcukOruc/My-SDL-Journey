#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <random>
#include <SDL2/Vector2.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

#define SCREEN_HEIGT 600
#define SCREEN_WIDTH 800

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

// PLAYER 1
SDL_Surface *firstplayerSurface;
SDL_Texture *firstplayerTexture;
#define FP_WIDTH 50
#define FP_HEIGHT 100
SDL_Rect fp_rect = {0, SCREEN_HEIGT / 2, FP_WIDTH, FP_HEIGHT};
int fp_posY = 0, fp_movSpeed = 10;
// PLAYER 2
SDL_Surface *secondplayerSurface;
SDL_Texture *secondplayerTexture;
#define SP_WIDTH 50
#define SP_HEIGHT 100
SDL_Rect sp_rect = {SCREEN_WIDTH - 50, SCREEN_HEIGT / 2, SP_WIDTH, SP_HEIGHT};
int sp_posY = 0, sp_movSpeed = 10;

// BALL
SDL_Surface *ballSurface;
SDL_Texture *ballTexture;
int ball_posX = 50, ball_posY = 50;
SDL_Rect ball_rect = {400, 400, 25, 25};
Vector2 ballDirections[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}, {0, 0}};
Vector2 currentDir;
float vX = SCREEN_WIDTH / 2, vY = SCREEN_HEIGT / 2, ballSpeed = 2200; // Default is 600
// DELTA TIME
Uint32 currentTime = 0;
Uint32 lastTime = 0;
float deltaTime = 0;

// SCORE
int p1Score, p2Score = 0;

// EXAMPLE TEXT
TTF_Font *font;
SDL_Color textColor;
SDL_Surface *textSurface;
SDL_Texture *textTexture;
SDL_Rect textRect;

void DrawText(string msg)
{

    font = TTF_OpenFont("arial.ttf", 28);
    textColor = {255, 255, 255};
    textSurface = TTF_RenderText_Solid(font, msg.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {SCREEN_WIDTH / 2, 0, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);
}

void IncreaseScore(int playerIndex)
{
    if (playerIndex == 1)
    {
        p1Score++;
        string totalScore_text = to_string(p1Score) + " : " + to_string(p2Score);
        DrawText(totalScore_text);
    }
    else if (playerIndex == 2)
    {
        p2Score++;
        string totalScore_text = to_string(p1Score) + " : " + to_string(p2Score);
        DrawText(totalScore_text);
    }
}

void InitializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        exit(-1);
    }
    if (TTF_Init() == -1)
    {
        exit(-1);
    }
}
void InitializeVideo()
{
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

int RandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    return distr(gen);
}

// BALL
void DrawBall()
{
    ballSurface = SDL_LoadBMP("Pong_Ball.bmp");
    ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    SDL_FreeSurface(ballSurface);
}
void MoveBall(float _deltatime)
{
    SDL_RenderClear(renderer);
    vX += ballSpeed * currentDir.x * _deltatime;
    vY += ballSpeed * currentDir.y * _deltatime;

    ball_rect.x = vX;
    ball_rect.y = vY;
}

// P1
void MoveFirstPlayer()
{
    SDL_RenderClear(renderer);
    fp_rect = {0, fp_posY, FP_WIDTH, FP_HEIGHT};
}
void DrawFirstPlayer()
{
    firstplayerSurface = SDL_LoadBMP("Pong_Player.bmp");
    firstplayerTexture = SDL_CreateTextureFromSurface(renderer, firstplayerSurface);
    SDL_FreeSurface(firstplayerSurface);
}

// P2
void DrawSecondPlayer()
{
    secondplayerSurface = SDL_LoadBMP("Pong_Player.bmp");
    secondplayerTexture = SDL_CreateTextureFromSurface(renderer, secondplayerSurface);
    SDL_FreeSurface(secondplayerSurface);
}
void MoveSecondPlayer()
{
    SDL_RenderClear(renderer);
    sp_rect = {SCREEN_WIDTH - 50, sp_posY, SP_WIDTH, SP_HEIGHT};
}

void Keyboard()
{
    switch (event.key.keysym.sym)
    {

    case SDLK_UP:
        fp_posY -= fp_movSpeed;
        MoveFirstPlayer();
        break;
    case SDLK_DOWN:
        fp_posY += fp_movSpeed;
        MoveFirstPlayer();
        break;

    case SDLK_w:
        sp_posY -= sp_movSpeed;
        MoveSecondPlayer();
        break;

    case SDLK_s:
        sp_posY += sp_movSpeed;
        MoveSecondPlayer();
        break;

    case SDLK_SPACE:

        break;

    default:
        break;
    }
}
void ProcessKeyboardInput()
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        Keyboard();
        break;

    default:
        break;
    }
}

void EventController()
{
    if (SDL_PollEvent(&event))
    {
        ProcessKeyboardInput();

        if (event.type == SDL_QUIT)
        {
            SDL_Quit();
        }
    }
}

Vector2 GORANDOMDIRECTION()
{
    int randDirIndex = RandomNumber(0, 8);

    if (currentDir.x != ballDirections[randDirIndex].x && currentDir.y != ballDirections[randDirIndex].y)
        return ballDirections[randDirIndex];
    else
    {
        return ballDirections[8];
    }
}

// COLLISION CONTROLLER
void HasFirstPlayerTouchedBall()
{
    if (SDL_HasIntersection(&fp_rect, &ball_rect))
    {
        // ball_rect.x += 10;
        currentDir = GORANDOMDIRECTION();
    }
}
void HasSecondPlayerTouchedBall()
{
    if (SDL_HasIntersection(&sp_rect, &ball_rect))
    {
        // ball_rect.x -= 10;

        currentDir = GORANDOMDIRECTION();
    }
}

void CollisionController()
{
    HasFirstPlayerTouchedBall();
    HasSecondPlayerTouchedBall();
}

int main(int argc, char *argv[])
{

    InitializeSDL();
    InitializeVideo();
    DrawFirstPlayer();
    DrawSecondPlayer();
    DrawBall();
    DrawText("0 : 0");

    currentDir = ballDirections[6];
    while (true)
    {

        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) * 1000.0f / (double)SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        MoveBall(deltaTime);
        EventController();

        // Player 1 Scores
        if (ball_rect.x < 0 + 10)
        {
            IncreaseScore(2);

            vX = 300;
            vY = 300;

            currentDir.x *= -1;
        }
        // Player 2 Scores
        else if (ball_rect.x > SCREEN_WIDTH - 35)
        {
            IncreaseScore(1);

            vX = 300;
            vY = 300;

            currentDir.x *= -1;
        }

        if (ball_rect.y < 0 + 10)
        {

            currentDir.y *= -1;
        }
        else if (ball_rect.y > SCREEN_HEIGT - 35)
        {

            currentDir.y *= -1;
        }

        SDL_RenderCopy(renderer, ballTexture, NULL, &ball_rect);
        SDL_RenderCopy(renderer, firstplayerTexture, NULL, &fp_rect);
        SDL_RenderCopy(renderer, secondplayerTexture, NULL, &sp_rect);
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        CollisionController();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(firstplayerTexture);
    SDL_DestroyTexture(secondplayerTexture);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}