#include "Game.h"
#include "MyHeaderFiles/Vector2.h"
class Input
{
private:
public:
    static bool OnKeyPressedDown(SDL_Keycode _targetKey, const SDL_Event &event);
    static bool OnKeyUp(SDL_Keycode _targetKey, const SDL_Event &event);
    static bool OnKeyDown(SDL_Keycode _targetKey, const SDL_Event &_event);
    static Vector2 MousePos();
    static bool IsMouseButtonDown(int _mouseButIndex, SDL_Event event);
};
