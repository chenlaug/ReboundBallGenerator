#include "Event.h"
#include <SDL_events.h>

bool Event::HandleEvents(bool& isRunning, bool& isPaused, bool& isFullWindow, SDL_Window* window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: // Ferme la fen�tre
            isRunning = false;
            break;

		case SDL_KEYDOWN: // Gestion des touches du clavier quand une touche est appuy�e
            switch (event.key.keysym.sym) {
            case SDLK_q: //  'Q' pour quitter
                isRunning = false;
                break;
            case SDLK_p: // 'P' Pause/relancer le jeu
                isPaused = !isPaused;
                break;
            case SDLK_f: // F'  Basculer en plein �cran
                if (isFullWindow) {
                    SDL_SetWindowFullscreen(window, 0); // D�sactiver le plein �cran
                    isFullWindow = false;
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // Activer le plein �cran
                    isFullWindow = true;
                }
                break;
            }
            break;

        case SDL_WINDOWEVENT: // G�rer les �v�nements li�s � la fen�tre
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;
                SDL_SetWindowSize(window, newWidth, newHeight); // G�rer le redimensionnement
            }
            break;
        }
    }
    return isRunning;
}