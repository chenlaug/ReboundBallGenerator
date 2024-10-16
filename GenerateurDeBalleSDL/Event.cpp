#include "Event.h"
#include <SDL_events.h>

bool Event::HandleEvents(bool& isRunning, bool& isPaused, bool& isFullWindow, SDL_Window* window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: // Ferme la fenêtre
            isRunning = false;
            break;

		case SDL_KEYDOWN: // Gestion des touches du clavier quand une touche est appuyée
            switch (event.key.keysym.sym) {
            case SDLK_q: //  'Q' pour quitter
                isRunning = false;
                break;
            case SDLK_p: // 'P' Pause/relancer le jeu
                isPaused = !isPaused;
                break;
            case SDLK_f: // F'  Basculer en plein écran
                if (isFullWindow) {
                    SDL_SetWindowFullscreen(window, 0); // Désactiver le plein écran
                    isFullWindow = false;
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // Activer le plein écran
                    isFullWindow = true;
                }
                break;
            }
            break;

        case SDL_WINDOWEVENT: // Gérer les événements liés à la fenêtre
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;
                SDL_SetWindowSize(window, newWidth, newHeight); // Gérer le redimensionnement
            }
            break;
        }
    }
    return isRunning;
}