#include "Game.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

Game::Game()
	: window("Balle", 1200, 600),
	renderer(window),
	fpsCounter(60),
	fpsText(nullptr),
	pauseText(nullptr),
	balleText(nullptr),
	isRunning(true), isPaused(false), isFullWindow(false),
	lastSpawnTime(0),
	spawnDelay(1000) {}

Game::~Game() {
	CleanUp();
}

void Game::Init() {
	if (!window.Init()) {
		std::cerr << "Erreur : Impossible d'initialiser la fenêtre." << std::endl;
		SDL_Quit();
		isRunning = false;
		return;
	}

	if (TTF_Init() == -1) {
		std::cerr << "Erreur lors de l'initialisation de SDL_ttf: " << TTF_GetError() << std::endl;
		isRunning = false;
		return;
	}

	if (!renderer.Init(window)) {
		std::cerr << "Erreur : Impossible d'initialiser le renderer." << std::endl;
		SDL_Quit();
		isRunning = false;
		return;
	}

	fpsCounter.Start();
	SDL_Color white = { 255, 255, 255, 255 };
	fpsText = new Text(renderer.GetSDLRenderer(), "../Font/Roboto-Medium.ttf", 24, white);
	if (!fpsText) {
		std::cerr << "Erreur lors du chargement de la police." << std::endl;
		isRunning = false;
	}
	fpsText->SetText("FPS: 0");

	pauseText = new Text(renderer.GetSDLRenderer(), "../Font/Roboto-Medium.ttf", 48, white);
	if (!pauseText) {
		std::cerr << "Erreur lors du chargement de la police." << std::endl;
		isRunning = false;
	}
	pauseText->SetText("Pause");
	srand(static_cast<unsigned int>(time(nullptr)));

	balleText = new Text(renderer.GetSDLRenderer(), "../Font/Roboto-Medium.ttf", 24, white);
	if (!balleText) {
		std::cerr << "Erreur lors du chargement de la police." << std::endl;
		isRunning = false;
	}
}


void Game::Run() {
	Init();

	while (isRunning) {
		eventHandler.HandleEvents(isRunning, isPaused, isFullWindow, &window, renderer.GetSDLRenderer());

		renderer.Clear();

		int windowWidth = window.GetWidth();
		int windowHeight = window.GetHeight();

		if (isPaused) {
			pauseText->Render(windowWidth / 2 - 50, windowHeight / 2 - 25);
		}
		else {
			Uint32 currentTime = SDL_GetTicks();
			if (currentTime - lastSpawnTime >= spawnDelay) {
				CircleType type = (rand() % 2 == 0) ? FILLED : OUTLINE;
				circles.emplace_back(window.GetWidth(), window.GetHeight(), type);
				lastSpawnTime = currentTime;
			}

			for (auto& circle : circles) {
				circle.Move(windowWidth, windowHeight);
				circle.Draw(renderer.GetSDLRenderer());
			}

			for (size_t i = 0; i < circles.size(); i++) {
				for (size_t j = i + 1; j < circles.size(); j++) {
					if (circles[i].CheckCollision(circles[j])) {
						circles[i].HandleCollision(circles[j]);
					}
				}

			}

			fpsCounter.Update();
			float fps = fpsCounter.GetFPS();
			fpsText->SetText("FPS: " + std::to_string(static_cast<int>(fps)));
			fpsText->Render(10, 10);

			balleText->SetText("balle nb : " + std::to_string(circles.size()));
			balleText->Render(10, 50);
		}

		renderer.Present();
	//	fpsCounter.LimitFPS();
	}

	CleanUp();
}



void Game::CleanUp() {
	if (fpsText) {
		delete fpsText;
		fpsText = nullptr;
	}

	if (pauseText) {
		delete pauseText;
		pauseText = nullptr;
	}

	if (balleText) {
		delete balleText;
		balleText = nullptr;
	}

	window.Clean();
	renderer.Clear();
	

	TTF_Quit();
	SDL_Quit();
	window.Clean();
}