module;
#include "raylib.h"
export module ball;

export struct Ball {
	float xPos, yPos;
	float speedX, speedY;
	float radius;
	Color ballColor;

	Ball() {}

	Ball(float xPos, float yPos, int radius, float speedX, float speedY, Color ballColor) :
		xPos(xPos),
		yPos(yPos),
		radius(radius),
		speedX(speedX),
		speedY(speedY),
		ballColor(ballColor)
	{}

	void Draw() {
		DrawCircle((int)xPos, (int)yPos, radius, ballColor);
	}
};