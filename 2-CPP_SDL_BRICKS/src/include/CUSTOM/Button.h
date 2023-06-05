struct Button
{
private:
    string buttonImg = "src/Images/ButtonImg.bmp";
    SDL_Surface *surface;
    SDL_Rect rect = {0, 0, 0, 0};
    function<void()> m_callback;

public:
    SDL_Texture *texture;
    Transform transform;
    Text *buttonText;
    Colors::Color hoverColor = Colors::Gray, defaultColor = Colors::White;

    // Plain Button
    Button(int w, int h, int x, int y, function<void()> _callBackFunction)
    {
        buttonText = nullptr;
        m_callback = _callBackFunction;

        surface = SDL_LoadBMP(buttonImg.c_str());

        transform.scale.x = w;
        transform.scale.y = h;
        transform.position.x = x;
        transform.position.y = y;

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rect = {transform.position.x, transform.position.y, transform.scale.x, transform.scale.y};
    }

    // Button With Text, You can't set offsets 0. I will improvise sth to debug that to user.
    Button(int w, int h, int x, int y, function<void()> _callBackFunction, string _buttonText, string _textFontStyle, int _textPuntoSize, Colors::Color _textColor, int t_offsetx, int t_offsety)
    {

        m_callback = _callBackFunction;

        surface = SDL_LoadBMP(buttonImg.c_str());

        transform.scale.x = w;
        transform.scale.y = h;
        transform.position.x = x;
        transform.position.y = y;

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rect = {transform.position.x, transform.position.y, transform.scale.x, transform.scale.y};

        buttonText = new Text{_buttonText, _textFontStyle, _textPuntoSize, _textColor};
        // by default it is 16,3 {Offsetts}
        buttonText->transform.position = Vector2{transform.position.x + (transform.scale.x / t_offsetx), transform.position.y + (transform.scale.y / t_offsety)};
    }
    Button() {}

private:
    bool IsHovering()
    {
        return (GetMousePosition().x >= transform.position.x && GetMousePosition().x < transform.position.x + transform.scale.x && GetMousePosition().y >= transform.position.y && GetMousePosition().y < transform.position.y + transform.scale.y);
    }

    void HoverController()
    {
        if (IsHovering() && IsMouseButtonDown(0))
            m_callback();
        else if (IsHovering())
            SDL_SetTextureColorMod(texture, hoverColor.r, hoverColor.g, hoverColor.b);
        else if (!IsHovering())
            SDL_SetTextureColorMod(texture, defaultColor.r, defaultColor.g, defaultColor.b);
    }

public:
    void RenderButton()
    {

        if (texture != NULL)
        {
            HoverController();
            rect = {transform.position.x, transform.position.y, transform.scale.x, transform.scale.y};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }

        if (buttonText->Text_Texture != NULL)
            buttonText->RenderText();
    }

    void DestroyButton()
    {
        buttonText->DestroyText();
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    // ~Button()
    // {
    //     DestroyButton();
    // }
};
