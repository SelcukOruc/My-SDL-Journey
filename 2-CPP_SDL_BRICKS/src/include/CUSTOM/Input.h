const Uint8 *keystates = SDL_GetKeyboardState(NULL);

bool IsPressedDown;
bool IsKeyUp;

bool OnKeyPressedDown(SDL_KeyCode _key)
{
    if (event.key.keysym.sym == _key)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (!IsPressedDown)
            {
                IsPressedDown = true;
                return true;
            }

            break;

        case SDL_KEYUP:
            IsPressedDown = false;
            break;
        }
    }
    return false;
}

bool OnKeyUp(SDL_KeyCode _key)
{
    if (event.key.keysym.sym == _key)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            IsKeyUp = false;
            break;

        case SDL_KEYUP:
            if (!IsKeyUp)
            {
                IsKeyUp = true;
                return true;
            }
            break;
        }
    }
    return false;
}

bool OnKeyDown(SDL_Scancode _key)
{
    if (keystates[_key])
        return true;
    else
        return false;
}

int MousePositionX, MousePositionY = 0;
Uint32 MouseState;

Vector2 GetMousePosition()
{
    MouseState = SDL_GetMouseState(&MousePositionX, &MousePositionY);
    return Vector2(MousePositionX, MousePositionY);
}

bool IsMouseButtonDown(int _mouseButIndex)
{

    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (_mouseButIndex == 0)
        {
            if (MouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
                return true;
        }
        else if (_mouseButIndex == 1)
        {
            if (MouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
                return true;
        }

        break;

    default:
        break;
    }
    return false;
}

bool IsMouseButtonUp(int _mouseButIndex)
{

    switch (event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if (_mouseButIndex == 0)
        {
            if (MouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
                return true;
        }
        else if (_mouseButIndex == 1)
        {
            if (MouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
                return true;
        }

        break;

    default:
        break;
    }
    return false;
}
