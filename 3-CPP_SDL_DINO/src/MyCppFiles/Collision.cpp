#include "MyHeaderFiles/Collision.h"
//
bool Collision::OnCollision(Transform &_othertransform, Transform &_maintransform, CollisionType _colType)
{
    bool collided = false;

    if (_colType == CollisionType::Exit)
    {
        if (!SDL_HasIntersection(&_othertransform.rect, &_maintransform.rect))
        {
            if (CONFIG::HasCollidedArray[_othertransform.Id])
            {
                CONFIG::HasCollidedArray[_othertransform.Id] = false;
                collided = true;
            }
        }
    }
    else if (_colType == CollisionType::Enter)
    {
        if (SDL_HasIntersection(&_othertransform.rect, &_maintransform.rect))
        {
            if (!CONFIG::HasCollidedArray[_othertransform.Id])
            {
                CONFIG::HasCollidedArray[_othertransform.Id] = true;
                collided = true;
            }
        }
        else
        {
            CONFIG::HasCollidedArray[_othertransform.Id] = false;
        }
    }
    else if (_colType == CollisionType::Stay)
    {
        if (SDL_HasIntersection(&_othertransform.rect, &_maintransform.rect))
        {
            return true;
        }
    }

    return collided;
}