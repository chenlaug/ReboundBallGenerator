#include "Game.h"
#include "Window.h"
#include <iostream>

Game::Game()
	: window("Mon Jeu SDL", 800, 600),
	renderer(window),
	isRunning(true), isPaused(false), isFullWindow(false) {}

Game::~Game() {
	Clenup();
}

void Game::Init() {
	if (!window.Init()) {  
		std::cerr << "Erreur : Impossible d'initialiser la fenêtre." << std::endl;
		isRunning = false;
		return;
	}

	if (!renderer.Init(window)) {
		std::cerr << "Erreur : Impossible d'initialiser le renderer." << std::endl;
		isRunning = false;
		return;
	}

	SDL_Color white = { 255, 255, 255, 255 };
	fpsText = new Text(renderer.GetSDLRenderer(), "../Font/Roboto-Medium.ttf", 24, white);
	fpsText->SetText("FPS: 0");
}


void Game::Run() {
	Init();
	while (isRunning)
	{
		eventHandler.HandleEvents(isRunning, isPaused, isFullWindow, window.GetSDLWindow());
		if (!isPaused) {
			renderer.Clear();

			fpsText->SetText("FPS : Laughan");
			fpsText->Render(10, 10);

			renderer.Present();
		}
	}
	Clenup();
}

void Game::Clenup() {
	window.Clean();
}