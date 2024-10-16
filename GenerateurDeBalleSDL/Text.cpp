#include "Text.h"
#include <iostream>

Text::Text(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, SDL_Color color)
    : renderer(renderer), font(nullptr), texture(nullptr), color(color) {
    if (!LoadFont(fontPath, fontSize)) {
        std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << std::endl;
    }
}

Text::~Text() {
    Clean(); 
}

bool Text::LoadFont(const std::string& fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void Text::SetText(const std::string& message) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface) {
        std::cerr << "Erreur lors de la creation de la surface du texte : " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Erreur lors de la creation de la texture du texte : " << SDL_GetError() << std::endl;
    }

    dstRect.w = surface->w;
    dstRect.h = surface->h;

    SDL_FreeSurface(surface);
}

void Text::Render(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect); 
    }
}

void Text::Clean() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void Text::SetColor(SDL_Color newColor) {
    color = newColor;
}
