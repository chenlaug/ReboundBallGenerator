#pragma once
#include <SDL.h>

enum CircleType {
	FILLED,   
	OUTLINE   
};

class Circle
{
private:
	int x, y;
	int radius;
	int speedX, speedY;
	SDL_Color color;
	CircleType type;
	int windowWidth, windowHeight;

public:
	Circle(int winW, int winH, CircleType circleType = FILLED);

	void Move();  
	void Draw(SDL_Renderer* renderer);  
	bool CheckCollision(const Circle& other) const;  
	void HandleCollision(Circle& other); 


	void SetRandomColor();
};

