module;
#include "raylib.h"
export module paddle;

export struct Paddle {
	float xPos, yPos;
	float speed;
	float width, height;

	Paddle() {}

	Paddle(float xPos, float yPos, float speed, float width, float height) :
		xPos(xPos),
		yPos(yPos),
		speed(speed),
		width(width),
		height(height)
	{}

	Rectangle GetRect() {
		return Rectangle{ xPos - width / 2, yPos - height / 2, 10, 100 };
	}

	void Draw() {
		DrawRectangleRec(GetRect(), WHITE);
	}
};