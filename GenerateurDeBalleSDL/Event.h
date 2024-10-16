#pragma once
#include <SDL.h>
#include "Renderer.h"
#include "Window.h"
class Event
{
public:
	bool HandleEvents(bool& isRunning, bool& isPaused, bool& isFullWindow, Window* window, SDL_Renderer* renderre);
};

