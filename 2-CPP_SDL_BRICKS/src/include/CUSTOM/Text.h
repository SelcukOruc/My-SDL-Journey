struct Text
{
private:
    string fontPath = FONT_PATH;

    TTF_Font *font;
    SDL_Surface *surfaceFont;
    SDL_Rect rect_text;
    SDL_Color sdlColor = {0, 0, 0};

public:
    SDL_Texture *Text_Texture;
    string fontName = "Sortie.ttf";
    int puntoSize = 25;
    string text = "";
    Colors::Color Text_Color = {255, 255, 255};

    Transform transform;

private:
    void LoadText()
    {
        surfaceFont = TTF_RenderText_Solid(font, text.c_str(), sdlColor);
        Text_Texture = SDL_CreateTextureFromSurface(renderer, surfaceFont);
    }

    void GetInitialTransform()
    {
        transform.scale.x = surfaceFont->w;
        transform.scale.y = surfaceFont->h;
        transform.position.x = 0;
        transform.position.y = 0;
    }

    void SetTransform()
    {
        // Updating transform.scale may not be efficient but if i don't it doesnt resize itself right after
        //...changing the text. So 'Till i find a solution to that problem it will stay like this.
        transform.scale.x = surfaceFont->w;
        transform.scale.y = surfaceFont->h;

        rect_text = {transform.position.x, transform.position.y, transform.scale.x, transform.scale.y};
    }

public:
    Text(string _text, string _fontName, int _puntoSize, Colors::Color _textColor)
    {
        text = _text;
        fontName = fontPath + _fontName;
        puntoSize = _puntoSize;

        SetColor(_textColor);

        font = TTF_OpenFont(fontName.c_str(), puntoSize);

        LoadText();

        GetInitialTransform();
        SetTransform();
    }
    Text() {}

    void SetText(string _newText)
    {
        text = _newText;
    }
    void SetColor(Colors::Color _newColor)
    {
        sdlColor.r = _newColor.r;
        sdlColor.g = _newColor.g;
        sdlColor.b = _newColor.b;
    }

    void RenderText()
    {
        LoadText();
        SetTransform();

        SDL_FreeSurface(surfaceFont);

        if (Text_Texture != NULL)
            SDL_RenderCopy(renderer, Text_Texture, NULL, &rect_text);
    }
    void DestroyText()
    {
        SDL_DestroyTexture(Text_Texture);
        Text_Texture = NULL;
    }

    ~Text()
    {
        DestroyText();
    }
};
