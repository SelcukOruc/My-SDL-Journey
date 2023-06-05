#include "MyHeaderFiles/Game.h"
#include "MyHeaderFiles/Sprite.h"
#include "MyHeaderFiles/Text.h"
#include <functional>
#include "MyHeaderFiles/Colors.h"
// First you create button, call the function 'ActivateButtonEvents' if button has any in 'UpdateEvents' and 'RenderButton' in 'Update'
class Button
{
private:
    bool IsHovering();
    function<void()> m_callback;
    bool active = true;
    Colors::Color hoverColor = Colors::Gray;

public:
    Sprite *buttonTexture;
    Text *buttonText;
    Button(SDL_Renderer *renderer, function<void()> _m_callback, int w, int h, string _buttonImgName);
    Button(SDL_Renderer *renderer, function<void()> _m_callback, int w, int h, string _buttonImgName, string _buttonMsg, string _textFont);
    Button();
    void RenderButton(SDL_Renderer *renderer);
    void ActivateButtonEvents(SDL_Event event);
    void ChangeButtonPosition(int x, int y, int _textOffsetX, int _textOffsetY);
    void ChangeHoverColor(Colors::Color _newColor);
    void SetActive(bool _isactive);
    bool IsActive();
    ~Button();
};
