#pragma once
#include <SDL.h>

class FPSCounter
{
private:
    Uint32 startTime;  
    int frameCount;     
    float currentFPS;   
    const int targetFPS;  
    const int frameDelay; 

public:
    FPSCounter(int fps = 60);
    void Start();         
    void Update();
    float GetFPS() const;  
    void LimitFPS();
};

