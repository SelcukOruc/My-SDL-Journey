#include "MyHeaderFiles/Button.h"
#include "MyHeaderFiles/Input.h"
#include "MyHeaderFiles/Colors.h"

void Button::ChangeButtonPosition(int x, int y, int _textOffsetX, int _textOffsetY)
{
    buttonTexture->transform->position->x = x;
    buttonTexture->transform->position->y = y;

    if (buttonText != nullptr)
    {

        buttonText->transform->position->x = buttonTexture->transform->position->x + _textOffsetX;
        buttonText->transform->position->y = buttonTexture->transform->position->y + _textOffsetY;
    }
}

Button::Button(SDL_Renderer *renderer, function<void()> _m_callback, int w, int h, string _buttonImgName)
{
    if (_buttonImgName == "")
        _buttonImgName = "ButtonImg";

    buttonText = nullptr;
    buttonTexture = new Sprite(renderer, _buttonImgName, w, h, false);
    m_callback = _m_callback;
}
Button::Button(SDL_Renderer *renderer, function<void()> _m_callback, int w, int h, string _buttonImgName, string _buttonMsg, string _textFont)
{
    if (_buttonImgName == "")
        _buttonImgName = "ButtonImg";

    buttonTexture = new Sprite(renderer, _buttonImgName, w, h, false);
    m_callback = _m_callback;
    buttonText = new Text(_buttonMsg, 25, _textFont, renderer);
}

Button::Button(){};

bool Button::IsHovering()
{
    return (Input::MousePos().x >= buttonTexture->transform->position->x && Input::MousePos().x < buttonTexture->transform->position->x + buttonTexture->transform->scale->x && Input::MousePos().y >= buttonTexture->transform->position->y && Input::MousePos().y < buttonTexture->transform->position->y + buttonTexture->transform->scale->y);
}

void Button::RenderButton(SDL_Renderer *renderer)
{
    if (active)
    {
        buttonTexture->UpdateSprite();
        if (buttonText != nullptr)
            buttonText->RenderText(renderer);
    }
}
void Button::ActivateButtonEvents(SDL_Event event)
{
    if (active)
    {
        if (IsHovering())
        {
            buttonTexture->ChangeColor(Button::hoverColor);
            if (Input::IsMouseButtonDown(0, event))
                m_callback();
        }
        else
            buttonTexture->ChangeColor(Colors::White);
    }
}

void Button::ChangeHoverColor(Colors::Color _newColor)
{
    hoverColor = _newColor;
}

bool Button::IsActive()
{
    return active;
}
void Button::SetActive(bool _isActive)
{
    active = _isActive;
}
Button::~Button()
{
    if (buttonText != nullptr)
    {
        delete buttonText;
    }
    delete buttonTexture;
}