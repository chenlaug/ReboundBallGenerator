#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    int offsetX, offsetY, d;
    offsetX = 0;
    offsetY = radius;
    d = radius - 1;
    while (offsetY >= offsetX) {
        SDL_RenderDrawPoint(renderer, x + offsetX, y + offsetY);
        SDL_RenderDrawPoint(renderer, x + offsetY, y + offsetX);
        SDL_RenderDrawPoint(renderer, x - offsetX, y + offsetY);
        SDL_RenderDrawPoint(renderer, x - offsetY, y + offsetX);
        SDL_RenderDrawPoint(renderer, x + offsetX, y - offsetY);
        SDL_RenderDrawPoint(renderer, x + offsetY, y - offsetX);
        SDL_RenderDrawPoint(renderer, x - offsetX, y - offsetY);
        SDL_RenderDrawPoint(renderer, x - offsetY, y - offsetX);
        if (d >= 2 * offsetX) {
            d -= 2 * offsetX + 1;
            offsetX += 1;
        }
        else if (d < 2 * (radius - offsetY)) {
            d += 2 * offsetY - 1;
            offsetY -= 1;
        }
        else {
            d += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
    }
}

float distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool CheckCollision(int x1, int y1, int radius1, int x2, int y2, int radius2) {
    float dist = distance(x1, y1, x2, y2);
    return dist <= (radius1 + radius2);
}

void HandleCollision(int& vx1, int& vy1, int& vx2, int& vy2) {
    std::swap(vx1, vx2);
    std::swap(vy1, vy2);
}

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Erreur lors de l'initialisation de SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }

    TTF_Font* font = TTF_OpenFont("../Font/Roboto-Medium.ttf", 24);
    if (!font) {
        std::cerr << "Erreur lors du chargement de la police: " << TTF_GetError() << std::endl;
        return -1;
    }

    bool isRunning = true;
    bool isPause = false;
    bool isFullWindows = false;
    int x = 800;
    int y = 600;

    SDL_Event event;
    SDL_Window* window = SDL_CreateWindow("Points avec SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        x, y,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int circleX = 400, circleY = 300;
    int circleX2 = 500, circleY2 = 300;

    int radius = 50;
    int radius2 = 30;

    int speedX = 3, speedY = 2;
    int speedX2 = 2, speedY2 = 3;

    Uint32 startTime = SDL_GetTicks();
    int frameCount = 0;

    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)) {
                isRunning = false;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
                isPause = !isPause;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_f) {
                    if (isFullWindows) {
                        SDL_SetWindowFullscreen(window, 0);
                        isFullWindows = false;
                    }
                    else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                        isFullWindows = true;
                    }
                }
            }

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int w = event.window.data1;
                int h = event.window.data2;
                SDL_RenderSetLogicalSize(renderer, w, h);
            }
        }

        if (isPause) {
            continue;
        }

        int winW, winH;
        SDL_GetWindowSize(window, &winW, &winH);

        circleX += speedX;
        circleY += speedY;

        if (circleX - radius <= 0 || circleX + radius >= winW) {
            speedX = -speedX;
        }
        if (circleY - radius <= 0 || circleY + radius >= winH) {
            speedY = -speedY;
        }

        circleX2 += speedX2;
        circleY2 += speedY2;

        if (circleX2 - radius2 <= 0 || circleX2 + radius2 >= winW) {
            speedX2 = -speedX2;
        }
        if (circleY2 - radius2 <= 0 || circleY2 + radius2 >= winH) {
            speedY2 = -speedY2;
        }

        if (CheckCollision(circleX, circleY, radius, circleX2, circleY2, radius2)) {
            HandleCollision(speedX, speedY, speedX2, speedY2);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DrawCircle(renderer, circleX, circleY, radius);
        DrawCircle(renderer, circleX2, circleY2, radius2);

        frameCount++;
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        float fps = frameCount / (elapsedTime / 1000.0f);

        RenderText(renderer, font, "FPS : " + std::to_string(static_cast<int>(fps)), 10, 10);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}