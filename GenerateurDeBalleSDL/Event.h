#pragma once
#include <SDL.h>
class Event
{
public:
	bool HandleEvents(bool& isRunning, bool& isPaused, bool& isFullWindow, SDL_Window* window);
};

