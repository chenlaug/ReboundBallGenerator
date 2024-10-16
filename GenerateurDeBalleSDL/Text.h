#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
private:
    SDL_Renderer* renderer; 
    TTF_Font* font;         
    SDL_Texture* texture;   
    SDL_Rect dstRect;       
    SDL_Color color;

public:
    Text(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, SDL_Color color);
    ~Text();

    bool LoadFont(const std::string& fontPath, int fontSize); 
    void SetText(const std::string& message);                 
    void Render(int x, int y);                                
    void Clean();                                             
    void SetColor(SDL_Color newColor);
};

