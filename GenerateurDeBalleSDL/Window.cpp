#include "Window.h"
#include <iostream>

Window::Window(const std::string& title, int width, int height)
    : window(nullptr), title(title), width(width), height(height) {}

Window::~Window() {
    Clean(); 
}

bool Window::Init() {
    window = SDL_CreateWindow(
        title.c_str(),                   
        SDL_WINDOWPOS_CENTERED,          
        SDL_WINDOWPOS_CENTERED,           
        width, height,                    
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE 
    );

    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Window::Clean() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}
