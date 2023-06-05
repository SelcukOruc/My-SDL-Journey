#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "MyHeaderFiles/Vector2.h"
#include "MyHeaderFiles/Game.h"
class Transform
{
public:
    Transform();
    int Id;
    SDL_Rect rect;
    Vector2 *position = new Vector2(0, 0);
    double rotation = 0;
    Vector2 *scale = new Vector2(0, 0);
    ~Transform();
};

#endif