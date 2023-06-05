#include "MyHeaderFiles/Game.h"
#include "MyHeaderFiles/Text.h"

Text::Text()
{
}

void Text::SetText(string _msg)
{
    string pathPlusFont = fontPATH + chosenPuntoName + ".ttf";
    font = TTF_OpenFont(pathPlusFont.c_str(), puntoSize);
    surfaceText = TTF_RenderText_Solid(font, _msg.c_str(), txtColor);
    textureText = SDL_CreateTextureFromSurface(selectedRenderer, surfaceText);
    currentTextMsg = _msg;
}

Text::Text(string _msg, int _puntoSize, string _fontName, SDL_Renderer *renderer)
{
    active = true;
    transform = new Transform();
    puntoSize = _puntoSize;
    chosenPuntoName = _fontName;
    selectedRenderer = renderer;

    SetText(_msg);

    transform->scale->x = surfaceText->w;
    transform->scale->y = surfaceText->h;
    txt_rect = {(int)transform->position->x, (int)transform->position->y, surfaceText->w, surfaceText->h};
}

void Text::RenderText(SDL_Renderer *renderer)
{
    if (active && transform != nullptr)
    {
        txt_rect.x = transform->position->x;
        txt_rect.y = transform->position->y;
        txt_rect.w = transform->scale->x;
        txt_rect.h = transform->scale->y;

        SDL_RenderCopy(renderer, textureText, nullptr, &txt_rect);
    }
}
// Before destroying, check if it is null. Otherwise, program is going to crash.
void Text::ChangeTextTo(string _newText)
{
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textureText);

    SetText(_newText);

    transform->scale->x = surfaceText->w;
    transform->scale->y = surfaceText->h;
    txt_rect = {(int)transform->position->x, (int)transform->position->y, surfaceText->w, surfaceText->h};
}

void Text::ChangePuntoTo(int _newPuntoSize)
{
    puntoSize = _newPuntoSize;
    ChangeTextTo(currentTextMsg);
}

void Text::ChangeTextColor(Colors::Color _newColor)
{
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textureText);

    txtColor.r = _newColor.r;
    txtColor.g = _newColor.g;
    txtColor.b = _newColor.b;

    SetText(currentTextMsg);
}

string Text::GetText()
{
    return currentTextMsg;
}
int Text::GetPuntoSize() { return puntoSize; }

bool Text::IsActive()
{
    return active;
}
void Text::SetActive(bool _state)
{
    active = _state;
}

Text::~Text()
{
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textureText);
    delete transform;
}