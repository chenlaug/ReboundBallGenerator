#include "Renderer.h"
#include "Constants.h"
#include <iostream>


Renderer::Renderer(Window& window) {
	SDL_Window* sdlWindow = window.GetSDLWindow();
	renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
}

bool Renderer::Init(Window& window) {
	renderer = SDL_CreateRenderer(window.GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderer != nullptr;
}

void Renderer::Clear() {
	SDL_Color white = { 255, 255, 255, 255 }; 
	SDL_Color black = { 0, 0, 0, 255 };      



	if (DARK_MODE) {
		SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a); // Noir
	}
	else {
		SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a); // Blanc
	}
	SDL_RenderClear(renderer);
}

void Renderer::Present() {
	SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::GetSDLRenderer() const {
	return renderer;
}