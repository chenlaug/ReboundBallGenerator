#pragma once
#include <SDL.h>
#include "Window.h"
class Renderer
{
private:
	SDL_Renderer* renderer;
public:

	Renderer(Window& window);
	~Renderer();

	bool Init(Window& window);
	void Clear();
	void Present();
	SDL_Renderer* GetSDLRenderer() const;
};

