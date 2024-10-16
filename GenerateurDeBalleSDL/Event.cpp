#include "Event.h"
#include <SDL_events.h>
#include "Window.h"
#include <iostream>

bool Event::HandleEvents(bool& isRunning, bool& isPaused, bool& isFullWindow, Window* window, SDL_Renderer* renderre) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: // Ferme la fen�tre
            isRunning = false;
            break;

		case SDL_KEYDOWN: // Gestion des touches du clavier quand une touche est appuy�e
            switch (event.key.keysym.sym) {
            case SDLK_q: //  'Q' pour quitter
            case SDLK_ESCAPE: //  'ESCAPE' pour quitter
                isRunning = false;
                break;
            case SDLK_p: // 'P' Pause/relancer le jeu
            case SDLK_SPACE: // 'SPACE' Pause/relancer le jeu
                isPaused = !isPaused;
                break;
            case SDLK_f: // 'F'  Basculer en plein �cran
                if (isFullWindow) {
                    SDL_SetWindowFullscreen(window->GetSDLWindow(), 0); // D�sactiver le plein �cran
                    isFullWindow = false;
                }
                else {
                    SDL_SetWindowFullscreen(window->GetSDLWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP); // Activer le plein �cran
                    isFullWindow = true;
                }
                break;
            }
            break;

        case SDL_WINDOWEVENT: // G�rer les �v�nements li�s � la fen�tre
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                window->SetWidth(event.window.data1);
                window->SetHeight(event.window.data2);
                //int newWidth = event.window.data1;
                //int newHeight = event.window.data2;
                //std::cout << event.window.data1 << std::endl;
                //SDL_RenderSetLogicalSize(renderre, newWidth, newHeight); // G�rer le redimensionnement
            }
            break;
        }
    }
    return isRunning;
}