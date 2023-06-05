bool HasCollidedList[COLLISION_LIMIT];

void SetCollisionLimit()
{
    for (int i = 0; i < COLLISION_LIMIT; i++)
    {
        HasCollidedList[i] = false;
    }
}

bool CheckCollision(Transform &other, Transform &_me)
{
    SDL_Rect me_converted_Rect = {_me.position.x, _me.position.y, _me.scale.x, _me.scale.y};
    SDL_Rect other_converted_Rect = {other.position.x, other.position.y, other.scale.x, other.scale.y};
    return SDL_HasIntersection(&me_converted_Rect, &other_converted_Rect);
}

bool OnCollisionEntered(Transform &_other, Transform &_me)
{
    if (CheckCollision(_other, _me))
    {
        if (!HasCollidedList[_me.m_ID])
        {
            HasCollidedList[_me.m_ID] = true;
            return true;
        }
    }
    // ON EXITED CHECK
    else
    {
        if (HasCollidedList[_me.m_ID])
        {
            HasCollidedList[_me.m_ID] = false;
            return false;
        }
    }
    return false;
}

bool OnCollisionExited(Transform &_other, Transform &_me)
{
    if (!CheckCollision(_other, _me))
    {
        if (HasCollidedList[_me.m_ID])
        {
            HasCollidedList[_me.m_ID] = false;
            return true;
        }
    }
    // ON ENTERED CHECK
    else
    {
        if (!HasCollidedList[_me.m_ID])
        {
            HasCollidedList[_me.m_ID] = true;
            return false;
        }
    }

    return false;
}