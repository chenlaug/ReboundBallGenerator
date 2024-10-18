#pragma once
#include "Window.h"
#include "Event.h"
#include "Renderer.h"
#include "Text.h"
#include "FPSCounter.h"
#include "Circle.h"
#include <vector>


class Game
{
private:
	Window window;
	Event eventHandler;
	Renderer renderer; 
	FPSCounter fpsCounter;  
	Text* fpsText;
	Text* balleText;
	Text* pauseText;  
	bool isRunning;
	bool isPaused;
	bool isFullWindow;

	std::vector<Circle> circles; 
	Uint32 lastSpawnTime;         
	Uint32 spawnDelay;


public:
	Game();
	~Game();
	void Init();
	void Run();
	void CleanUp();
	bool IsPositionFree(int newX, int newY, int newRadius, const std::vector<Circle>& circles);

};

