#include "Game.h"
#include "Window.h"
#include "Renderer.h"
#include "Circle.h"
#include <iostream>
#include "Constants.h"

Game::Game()
	: window(WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y),
	renderer(window),
	fpsCounter(LIMIT_FPS),
	fpsText(nullptr),
	pauseText(nullptr),
	balleText(nullptr),
	isRunning(IS_RUNNING), isPaused(IS_PAUSED), isFullWindow(IS_FULL_WINDOW),
	lastSpawnTime(LAST_SPAWN_TIME),
	spawnDelay(SPAWN_DELAY) {}

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
	SDL_Color white = { 255,255,255,255 };
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
	Uint32 frameStart;
	Init();

	while (isRunning) {
		frameStart = SDL_GetTicks();
		eventHandler.HandleEvents(isRunning, isPaused, isFullWindow, &window, renderer.GetSDLRenderer());

		renderer.Clear();

		int windowWidth = window.GetWidth();
		int windowHeight = window.GetHeight();

		if (isPaused) {
			pauseText->Render(windowWidth / 2 - 50, windowHeight / 2 - 25);
		}
		else {
			Uint32 currentTime = SDL_GetTicks();
			if ((currentTime - lastSpawnTime) >= spawnDelay) {
				int newX, newY, newRadius;
				bool positionFound = false;

				while (!positionFound) {
					newRadius = 10 + rand() % 20;
					newX = newRadius + rand() % (windowWidth - 2 * newRadius);
					newY = newRadius + rand() % (windowHeight - 2 * newRadius);

					if (IsPositionFree(newX, newY, newRadius, circles)) {
						positionFound = true;
					}
				}

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

			balleText->SetText("Nombre de balle: " + std::to_string(circles.size()));
			balleText->Render(10, 50);
		}

		renderer.Present();
		fpsCounter.LimitFPS(frameStart);
	}

	CleanUp();
}


bool Game::IsPositionFree(int newX, int newY, int newRadius, const std::vector<Circle>& circles)
{
	for (const auto& circle : circles) {
		int distX = newX - circle.GetX();
		int distY = newY - circle.GetY();
		int distanceSquared = distX * distX + distY * distY;
		int combinedRadius = newRadius + circle.GetRadius();

		if (distanceSquared < combinedRadius * combinedRadius) {
			return false;
		}
	}
	return true;
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

