#ifndef TEXT_H
#define TEXT_H

#include "MyHeaderFiles/Game.h"
#include "include/SDL_ttf.h"
#include "MyHeaderFiles/Transform.h"
#include "MyHeaderFiles/Colors.h"

class Text
{
private:
    TTF_Font *font;
    SDL_Color txtColor = {255, 255, 255};
    SDL_Surface *surfaceText;
    SDL_Texture *textureText;
    SDL_Rect txt_rect;
    string fontPATH = "src/Fonts/";

    bool active = true;
    string currentTextMsg = "";
    int puntoSize = 0;
    string chosenPuntoName = "";
    SDL_Renderer *selectedRenderer;

    void SetText(string _msg);

public:
    Transform *transform;
    Text(string _msg, int _puntoSize, string _fontName, SDL_Renderer *renderer);
    Text();
    void RenderText(SDL_Renderer *renderer);
    // This is not very efficient way of changing text. Using frequently [update (etc.)] is not recommended.
    void ChangeTextTo(string _newText);
    // This is not very efficient way of changing puntoSize. Using frequently [ in update (etc.)] is not recommended.
    void ChangePuntoTo(int _newPuntoSize);
    // This is not very efficient way of changing color. Using frequently [ in update (etc.)] is not recommended.
    void ChangeTextColor(Colors::Color _newColor);
    void ChageFontTo(string _newFontName);

    bool IsActive();
    void SetActive(bool _state);

    string GetText();
    int GetPuntoSize();

    ~Text();
};
#endif