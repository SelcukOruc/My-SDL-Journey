#define SPRITE_H
#ifdef SPRITE_H

#include "Game.h"
#include "MyHeaderFiles/Transform.h"
#include "MyHeaderFiles/Colors.h"
// DONT FORGET TO DESTROY SPRITE AFTER YOU DONE WITH IT.

class Sprite
{
private:
    string textureName = "";
    string path = "src/Images/";
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    bool active = true;
    bool HasAnimation = false;
    float mycounter = 0;
    int currentFrame = 0;

public:
    SDL_Rect rect_src;
    Transform *transform;
    Sprite(SDL_Renderer *_renderer, string _texturename, int w, int h, bool _hasAnimation);
    void UpdateSprite();
    void ChangeColor(Colors::Color _newColor);
    void Animate(int tile_w, int tile_h, float _animDelay, float _dTime, float _imgWidth);
    bool IsActive();
    void SetActive(bool _isActive);
    ~Sprite();
};
#endif