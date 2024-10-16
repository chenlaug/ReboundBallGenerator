#pragma once
#include <SDL.h>
#include <string>

class Window {
private:
	SDL_Window* window;
	std::string title;
	int width;
	int height;

public:
	Window(const std::string& title, int width, int height);
	~Window();
	bool Init();
	void Clean();
	SDL_Window* GetSDLWindow() const;
	int GetWidth() const;
	int GetHeight() const;
};

