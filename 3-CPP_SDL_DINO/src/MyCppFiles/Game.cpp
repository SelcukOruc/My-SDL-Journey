#include "MyHeaderFiles/Game.h"
#include "MyHeaderFiles/Button.h"
#include "MyHeaderFiles/Time.h"
#include "MyHeaderFiles/Collision.h"
#include "MyHeaderFiles/Input.h"
#include "MyHeaderFiles/Text.h"

bool IsGameRunning = false;
Button *startButton;

Sprite *dino;
Sprite *background1, *background2;
Sprite *Obstacle1;
Sprite *Obstacle3;

float bgMoveSpeed = 0.16;
float deltatime;
float jumpHeight = 115;
float gravityForce = 0.11;

bool canJump = true;

Text *scoreText;

int currentScore = 0;
void ChangeScore(int _amount)
{
    currentScore += _amount;
    scoreText->ChangeTextTo(to_string(currentScore));
}

void StartGame()
{
    currentScore = 0;
    ChangeScore(0);

    IsGameRunning = true;
    startButton->SetActive(false);
    dino->SetActive(true);
}
void OnDeath()
{
    IsGameRunning = false;
    dino->SetActive(false);
    startButton->SetActive(true);
    cout << "END " << endl;
}

void CheckCollisions()
{
    if (Collision::OnCollision(*Obstacle1->transform, *dino->transform, CollisionType::Enter))
    {
        OnDeath();
        Obstacle1->SetActive(false);
    }
    if (Collision::OnCollision(*Obstacle3->transform, *dino->transform, CollisionType::Enter))
    {
        OnDeath();
        Obstacle3->SetActive(false);
    }
}

void MoveBackgroundAndObstacles()
{
    background1->transform->position->x -= deltatime * bgMoveSpeed;
    background2->transform->position->x -= deltatime * bgMoveSpeed;

    if (background1->transform->position->x < -400)
    {
        Obstacle1->SetActive(true);
        background1->transform->position->x = 400;
        ChangeScore(1);
    }

    if (background2->transform->position->x < -400)
    {
        Obstacle3->SetActive(true);
        background2->transform->position->x = 400;
        ChangeScore(1);
    }

    Obstacle1->transform->position->x = background1->transform->position->x;
    Obstacle3->transform->position->x = background2->transform->position->x;
}

void ApplyGravity()
{
    if (dino->transform->position->y < 450)
    {
        canJump = false;
        dino->transform->position->y += gravityForce * deltatime;
    }
    else if (dino->transform->position->y > 450)
        canJump = true;
}

void Game::Start()
{
    currentScore = 0;

    startButton = new Button{renderer, StartGame, 256, 135, "StartButtonDino"};
    startButton->ChangeButtonPosition(75, 200, 0, 0);
    startButton->ChangeHoverColor(Colors::Gray);

    dino = new Sprite{renderer, "DinoMove", 48, 48, true};
    dino->transform->position->y = 450;
    dino->transform->position->x = 150;

    background1 = new Sprite{renderer, "background", 400, 600, false};
    background2 = new Sprite{renderer, "background", 400, 600, false};
    background2->transform->position->x = 400;

    Obstacle1 = new Sprite{renderer, "obstacle_single", 20, 80, false};
    Obstacle1->transform->position->y = 450;
    Obstacle1->transform->position->x = 400;

    Obstacle3 = new Sprite{renderer, "obstacle_triple", 40, 80, false};
    Obstacle3->transform->position->y = 450;
    Obstacle3->transform->position->x = 400;

    scoreText = new Text{"0", 35, "Sortie", renderer};
    scoreText->transform->position->x = 200;
    scoreText->transform->position->y = 50;
}
void Game::UpdateEvent(const SDL_Event &event)
{
    startButton->ActivateButtonEvents(event);

    if (Input::OnKeyPressedDown(SDLK_SPACE, event) && canJump)
    {
        canJump = false;
        dino->transform->position->y -= jumpHeight;
    }
}
void Game::Update()
{

    if (IsGameRunning)
    {
        deltatime = Time::deltaTime();
        MoveBackgroundAndObstacles();
        ApplyGravity();
    }

    dino->Animate(24, 24, 50, deltatime, 144);

    background1->UpdateSprite();
    background2->UpdateSprite();
    Obstacle1->UpdateSprite();
    Obstacle3->UpdateSprite();
    dino->UpdateSprite();

    CheckCollisions();

    startButton->RenderButton(renderer);
    scoreText->RenderText(renderer);
}
void Game::OnAppQuit()
{
}
