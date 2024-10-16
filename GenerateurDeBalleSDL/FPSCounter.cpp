#include "FPSCounter.h"

FPSCounter::FPSCounter(int fps)
    : startTime(0), frameCount(0), currentFPS(0.0f), targetFPS(fps), frameDelay(1000 / fps) {}

void FPSCounter::Start() {
    startTime = SDL_GetTicks();  
    frameCount = 0;
    currentFPS = 0.0f;
}

void FPSCounter::Update() {
    frameCount++;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - startTime >= 1000) {  
        currentFPS = frameCount / ((currentTime - startTime) / 1000.0f);  
        startTime = currentTime;  
        frameCount = 0;  
    }
}

float FPSCounter::GetFPS() const {
    return currentFPS; 
}

void FPSCounter::LimitFPS() {
    Uint32 frameStart = SDL_GetTicks(); 


    Uint32 frameTime = SDL_GetTicks() - frameStart;

   
    if (frameTime < frameDelay) {
        SDL_Delay(frameDelay - frameTime);
    }
}
