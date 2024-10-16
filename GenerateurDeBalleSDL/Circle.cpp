#include "Circle.h"
#include <cmath>
#include <algorithm>

Circle::Circle(int winW, int winH, CircleType circleType)
    : windowWidth(winW), windowHeight(winH), type(circleType) {
    x = rand() % winW;
    y = rand() % winH;

    radius = 10 + rand() % 20;

    speedX = -5 + rand() % 11;
    speedY = -5 + rand() % 11;

    SetRandomColor();
}

void Circle::SetRandomColor() {
    color = { static_cast<Uint8>(rand() % 256),
             static_cast<Uint8>(rand() % 256),
             static_cast<Uint8>(rand() % 256),
             255 };  
}

void Circle::Move(int windowWidth, int windowHeight) {
    x += speedX;
    y += speedY;

    if (x - radius <= 0 || x + radius >= windowWidth) {
        speedX = -speedX;
    }
    if (y - radius <= 0 || y + radius >= windowHeight) {
        speedY = -speedY;
    }
}

void Circle::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (type == FILLED) {
        for (int w = 0; w < radius * 2; w++) {
            for (int h = 0; h < radius * 2; h++) {
                int dx = radius - w; 
                int dy = radius - h; 
                if ((dx * dx + dy * dy) <= (radius * radius)) {
                    SDL_RenderDrawPoint(renderer, x + dx - radius, y + dy - radius);
                }
            }
        }
    }
    else if (type == OUTLINE) {
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
                offsetX++;
            }
            else if (d < 2 * (radius - offsetY)) {
                d += 2 * offsetY - 1;
                offsetY--;
            }
            else {
                d += 2 * (offsetY - offsetX - 1);
                offsetY--;
                offsetX++;
            }
        }
    }
}

bool Circle::CheckCollision(const Circle& other) const {
    int distX = x - other.x;
    int distY = y - other.y;
    int distance = sqrt(distX * distX + distY * distY);
    return distance <= (radius + other.radius);
}

void Circle::HandleCollision(Circle& other) {
    std::swap(speedX, other.speedX);
    std::swap(speedY, other.speedY);
}
