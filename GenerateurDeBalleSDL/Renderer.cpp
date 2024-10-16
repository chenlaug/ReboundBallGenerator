#include "Renderer.h"
#include <iostream>


Renderer::Renderer(Window& window) {
	SDL_Window* sdlWindow = window.GetSDLWindow(); 
	if (!sdlWindow) {
		std::cerr << "Erreur: la fenetre SDL n'est pas valide." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "Erreur lors de la création du renderer: " << SDL_GetError() << std::endl;
	}
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	SDL_RenderClear(renderer);
}

void Renderer::Present() {
	SDL_RenderPresent(renderer); 
}

SDL_Renderer* Renderer::GetSDLRenderer() const {
	return renderer;
}