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

    if (window == nullptr) {  
        std::cerr << "Erreur lors de la cr�ation de la fen�tre: " << SDL_GetError() << std::endl;
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

SDL_Window* Window::GetSDLWindow() const {
	return window;
}

int Window::GetWidth() const {
	return width;
}

void Window::SetWidth(int newWidth)
{
    width = newWidth;
}

int Window::GetHeight() const {
	return height;
}

void Window::SetHeight(int newHeight)
{
    height = newHeight;
}
