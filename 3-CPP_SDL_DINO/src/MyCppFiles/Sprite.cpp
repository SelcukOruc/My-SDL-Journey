#include "MyHeaderFiles/Sprite.h"

Sprite::Sprite(SDL_Renderer *_renderer, string _texturename, int w, int h, bool _hasAnimation)
{

    renderer = _renderer;
    textureName = path + _texturename + ".bmp";
    surface = SDL_LoadBMP(textureName.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    HasAnimation = _hasAnimation;

    if (w <= -1)
        w = surface->w;
    if (h <= -1)
        h = surface->h;

    transform = new Transform();
    transform->scale->x = w;
    transform->scale->y = h;

    active = true;
}
void Sprite::UpdateSprite()
{
    if (active)
    {
        int x = transform->position->x;
        int y = transform->position->y;
        int w = transform->scale->x;
        int h = transform->scale->y;

        transform->rect = {x, y, w, h};
        SDL_Point center = {transform->rect.w / 2, transform->rect.h / 2};

        if (!HasAnimation)
            SDL_RenderCopyEx(renderer, texture, NULL, &transform->rect, transform->rotation, &center, SDL_FLIP_NONE);
        else
            SDL_RenderCopyEx(renderer, texture, &rect_src, &transform->rect, transform->rotation, &center, SDL_FLIP_NONE);
    }
}
void Sprite::ChangeColor(Colors::Color _newColor)
{
    SDL_SetTextureColorMod(texture, _newColor.r, _newColor.g, _newColor.b);
}

// title_w and title_h : indicates original width and height of image you want to animate, not scale.
// Image width : is not same thing with transform.scale, you need to provide original width of image you want to animate.
void Sprite::Animate(int tile_w, int tile_h, float _animDelay, float _dTime, float _imgWidth)
{
    mycounter += _dTime;
    if (currentFrame > (_imgWidth / tile_w) - 1)
        currentFrame = 0;

    if (mycounter > _animDelay)
    {
        mycounter = 0;
        currentFrame++;
    }

    rect_src.w = tile_w;
    rect_src.h = tile_h;
    rect_src.x = currentFrame * tile_w;
    rect_src.y = 0;
}

// Before destroying, check if it is null. Otherwise, program is going to crash.
bool Sprite::IsActive()
{
    return active;
}

void Sprite::SetActive(bool _isActive)
{
    active = _isActive;
}

Sprite::~Sprite()
{
    active = false;
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    delete transform;
}