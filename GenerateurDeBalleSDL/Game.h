#pragma once
#include "Window.h"
#include "Event.h"
#include "Renderer.h"
#include "Text.h"


class Game
{
private:
	Window window;
	Event eventHandler;
	Renderer renderer; 
	Text* fpsText;
	bool isRunning;
	bool isPaused;
	bool isFullWindow;

public:
	Game();
	~Game();
	void Init();
	void Run();
	void Clenup();
};

