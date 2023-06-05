bool HasGameStarted = false;

Text *CanText;
Button *StartButton;
Text *ScoreText;
int Score = 0;
Sprite *wall_right, *wall_left, *wall_up;
Sprite *paddle;
Sprite *ball;
float paddleMovSpeed = 0.5;
float ballMovSpeed = 0.35;
float ballVelocityX = 1, ballVelocityY = -1;

#define BRICK_NUMBER 90
#define ROW_LIMIT 15
#define BRICK_SCALE_W 60
#define BRICK_SCALE_H 25
#define INITIAL_BRICK_POS_X 150
#define INITIAL_BRICK_POS_Y 100

int BrickNumberLeft = BRICK_NUMBER;

struct Brick
{
    Sprite *brickSprite;
    int brickState = 2;

    void ChangeBrickState()
    {

        brickState--;
        if (brickState == 2)
            brickSprite->ChangeColor(Colors::yellow);
        else if (brickState == 1)
            brickSprite->ChangeColor(Colors::Red);
        else if (brickState <= 0)
            DestroyBrick();

        ChangeBallDirection();
    }

    void DestroyBrick()
    {
        brickSprite->transform._objectName = "DEAD";
        brickSprite->DestroySprite();
        Score++;
        ScoreText->text = to_string(Score);
    }

    void ChangeBallDirection()
    {
        int r = RandomNumber(0, 50);
        if (r > 25)
            ballVelocityX = -1;
        else
            ballVelocityX = 1;
        ballVelocityY = ballVelocityY * -1;
    }
};

Brick *bricks[BRICK_NUMBER];
int currentBrickPosY = INITIAL_BRICK_POS_Y, currentBrickPosX = INITIAL_BRICK_POS_X, gapX = BRICK_SCALE_W + 5, gapY = BRICK_SCALE_H + 5;
int brickCounter = 0;

void CreateBricks()
{
    for (int i = 0; i < BRICK_NUMBER; i++)
    {

        if (i == 0)
        {
            bricks[i] = new Brick{new Sprite{"BaseTexture.bmp", currentBrickPosX, currentBrickPosY}};
            bricks[i]->brickSprite->transform.scale.x = BRICK_SCALE_W;
            bricks[i]->brickSprite->transform.scale.y = BRICK_SCALE_H;
        }
        else
        {
            bricks[i] = new Brick{new Sprite{"BaseTexture.bmp", 0, 0}};
            bricks[i]->brickSprite->transform.scale.x = BRICK_SCALE_W;
            bricks[i]->brickSprite->transform.scale.y = BRICK_SCALE_H;

            bricks[i]->brickSprite->transform.position.x = currentBrickPosX;
            bricks[i]->brickSprite->transform.position.y = currentBrickPosY;
            currentBrickPosX += gapX;
        }

        bricks[i]->brickSprite->ChangeColor(Colors::Green);

        if (brickCounter >= ROW_LIMIT)
        {
            brickCounter = 0;
            currentBrickPosX = INITIAL_BRICK_POS_X;
            currentBrickPosY += gapY;
        }
        brickCounter++;
    }
}

void RenderBricks()
{
    for (int i = 0; i < BRICK_NUMBER; i++)
    {
        bricks[i]->brickSprite->RenderSprite();
    }
}

void CheckBricksCollision()
{
    for (int i = 0; i < BRICK_NUMBER; i++)
    {
        if (bricks[i]->brickSprite->transform._objectName != "DEAD")
            if (OnCollisionEntered(ball->transform, bricks[i]->brickSprite->transform))
                bricks[i]->ChangeBrickState();
    }
}

void CreateWalls()
{
    wall_up = new Sprite{"BaseTexture.bmp", 0, 0};
    wall_up->transform.scale.x = SCREEN_WIDTH;
    wall_up->transform.scale.y = 10;
    wall_up->transform._objectName = "WALL UP";

    wall_right = new Sprite{"BaseTexture.bmp", SCREEN_WIDTH - 10, 0};
    wall_right->transform.scale.x = 10;
    wall_right->transform.scale.y = SCREEN_HEIGHT;
    wall_right->transform._objectName = "WALL RIGHT";

    wall_left = new Sprite{"BaseTexture.bmp", 0, 0};
    wall_left->transform.scale.x = 10;
    wall_left->transform.scale.y = SCREEN_HEIGHT;
    wall_right->transform._objectName = "WALL LEFT";
}
void RenderWalls()
{
    wall_up->RenderSprite();
    wall_left->RenderSprite();
    wall_right->RenderSprite();
}

void CreateBall()
{
    ball = new Sprite{"BaseTexture.bmp", 520, 600};
    ball->transform.scale.x = 15;
    ball->transform.scale.y = 15;
}
void MoveBall(float _velocityX, float _velocityY)
{
    ball->transform.position.x += ballMovSpeed * deltaTime * _velocityX;
    ball->transform.position.y -= ballMovSpeed * deltaTime * _velocityY;
}

void CreatePaddle()
{
    paddle = new Sprite{"BaseTexture.bmp", 570, 700};
    paddle->transform.scale.x = 175;
    paddle->transform.scale.y = 15;
}
void MovePaddle(int _dir)
{
    paddle->transform.position.x += paddleMovSpeed * deltaTime * _dir;
}

void ChangeBallDirection(int _x, int _y)
{
    ballVelocityX = _x;
    ballVelocityY = _y;
}
void HandleInput()
{
    if (OnKeyDown(SDL_SCANCODE_LEFT))
        MovePaddle(-1);
    else if (OnKeyDown(SDL_SCANCODE_RIGHT))
        MovePaddle(1);
}
void HandleCollision()
{
    // On 'Ball' Collided With 'Paddle'
    if (OnCollisionEntered(ball->transform, paddle->transform))
    {
        // cout << to_string(abs(ball->transform.position.x - paddle->transform.position.x)) << endl;
        // Straight
        if (abs(ball->transform.position.x - paddle->transform.position.x) < 100 && abs(ball->transform.position.x - paddle->transform.position.x) > 70)
            ChangeBallDirection(0, 1);
        // Right
        else if (abs(ball->transform.position.x - paddle->transform.position.x) > 50)
            ChangeBallDirection(1, 1);
        // Left
        else if (abs(ball->transform.position.x - paddle->transform.position.x) < 50)
            ChangeBallDirection(-1, 1);
    }
    // On 'Ball' Collided With 'LEFT WALL'
    if (OnCollisionEntered(ball->transform, wall_left->transform))
    {
        if (ballVelocityY == -1)
            ChangeBallDirection(1, -1);
        else
            ChangeBallDirection(1, 1);
    }
    // On 'Ball' Collided With 'WALL UP'
    if (OnCollisionEntered(ball->transform, wall_up->transform))
    {
        int r = RandomNumber(0, 10);

        if (r > 5)
            ChangeBallDirection(-1, -1);
        else
            ChangeBallDirection(1, -1);
    }
    // On 'Ball' Collided With 'RIGHT WALL'
    if (OnCollisionEntered(ball->transform, wall_right->transform))
    {
        if (ballVelocityY == -1)
            ChangeBallDirection(-1, -1);
        else
            ChangeBallDirection(-1, 1);
    }
}

void StartGame()
{
    CreateBricks();
    CreateBall();
    CreatePaddle();
    CreateWalls();

    ScoreText = new Text{"00", "Sortie.ttf", 40, Colors::Orange};
    ScoreText->transform.position.x = 20;
    ScoreText->transform.position.y = 35;
    ScoreText->text = to_string(Score);

    HasGameStarted = true;
    StartButton->DestroyButton();
}

void Awake()
{
}
void Start()
{
    StartButton = new Button{350, 100, 450, 300, StartGame, "Start Game !", "Sortie.ttf", 45, Colors::Orange, 5, 3};
    CanText = new Text{"CAN MRB", "Sortie.ttf", 35, Colors::White};
    CanText->transform.position = Vector2(555, 247);
}
void Update()
{
    if (HasGameStarted)
    {
        MoveBall(ballVelocityX, ballVelocityY);
        HandleInput();
        HandleCollision();
        CheckBricksCollision();
        ball->RenderSprite();
        paddle->RenderSprite();
        RenderWalls();
        RenderBricks();
        ScoreText->RenderText();
        paddle->transform.EditorMode();
    }
    StartButton->RenderButton();
}

void OnApplicationQuit()
{
}