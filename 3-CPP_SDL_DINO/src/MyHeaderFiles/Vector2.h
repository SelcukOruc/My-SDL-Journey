#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdio.h>
struct Vector2
{
public:
    float y, x;
    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    };
};
#endif