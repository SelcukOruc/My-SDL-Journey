struct Sprite
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;

public:
    Transform transform;

public:
    void ChangeSprite(string _newSpriteName)
    {
        surface = SDL_LoadBMP((IMAGE_PATH + _newSpriteName).c_str());
        transform.scale.x = surface->w;
        transform.scale.y = surface->h;
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect = {transform.position.x, -transform.position.y, transform.scale.x, transform.scale.y};
        SDL_FreeSurface(surface);
    }

    Sprite(std::string _spriteName, int _posX, int _posY)
    {

        transform.position.x = _posX;
        transform.position.y = _posY;
        ChangeSprite(_spriteName);
    }
    Sprite() {}

    void ChangeColor(Colors::Color new_color)
    {
        SDL_SetTextureColorMod(texture, new_color.r, new_color.g, new_color.b);
    }

    void RenderSprite()
    {
        rect = {transform.position.x, transform.position.y, transform.scale.x, transform.scale.y};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void DestroySprite()
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    ~Sprite()
    {
        DestroySprite();
    }
};
