#ifndef COLLISION_H
#define COLLISION_H

#include "MyHeaderFiles/Game.h"
#include "MyHeaderFiles/CONFIG.h"
#include "MyHeaderFiles/Transform.h"

enum CollisionType
{
    Exit,
    Enter,
    Stay
};

class Collision
{
private:
public:
    static bool OnCollision(Transform &_othertransform, Transform &_maintransform, CollisionType _colType);
};
#endif