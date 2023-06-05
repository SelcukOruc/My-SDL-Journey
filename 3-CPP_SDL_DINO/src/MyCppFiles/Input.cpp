#include "MyHeaderFiles/Input.h"
#include <unordered_map>

std::unordered_map<SDL_Keycode, bool> keyStates;
static Uint32 MouseState;
static int MousePosX, MousePosY;

bool Input::OnKeyDown(SDL_Keycode _targetKey, const SDL_Event &event)
{
    if (event.key.keysym.sym == _targetKey && event.type == SDL_KEYDOWN)
    {
        keyStates[_targetKey] = true;
        return true;
    }
    return false;
}

bool Input::OnKeyUp(SDL_Keycode _targetKey, const SDL_Event &event)
{
    if (event.key.keysym.sym == _targetKey && event.type == SDL_KEYUP)
    {
        keyStates[_targetKey] = false;
        return true;
    }
    else if (event.key.keysym.sym == _targetKey && event.type == SDL_KEYDOWN)
    {
        keyStates[_targetKey] = true;
    }
    return false;
}
bool Input::OnKeyPressedDown(SDL_Keycode _targetKey, const SDL_Event &event)
{
    if (event.key.keysym.sym == _targetKey && event.type == SDL_KEYDOWN)
    {
        if (!keyStates[_targetKey])
        {
            keyStates[_targetKey] = true;
            return true;
        }
    }
    else if (event.key.keysym.sym == _targetKey && event.type == SDL_KEYUP)
    {
        keyStates[_targetKey] = false;
    }
    return false;
}

Vector2 Input::MousePos()
{
    MousePosX = 0;
    MousePosY = 0;
    MouseState = 0;

    MouseState = SDL_GetMouseState(&MousePosX, &MousePosY);
    return Vector2(MousePosX, MousePosY);
}

bool Input::IsMouseButtonDown(int _mouseButIndex, SDL_Event event)
{
    Input::MousePos();
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
