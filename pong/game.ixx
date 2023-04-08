module;
#include "raylib.h"
#include <string>
export module game;
import constants;
import ball;
import paddle;
import IfileHandler;
import fileHandlerTxt;

export struct Game
{
	int start() {
		InitWindow(GameConstants::GAME_WINDOW_WIDTH, GameConstants::GAME_WINDOW_HEIGHT, GameConstants::GAME_WINDOW_TITLE.c_str());
		SetWindowState(FLAG_VSYNC_HINT);

		IfileHandler* x = new fileHandlerTxt();

		Ball ball(
			GameConstants::BALL_X_POS,
			GameConstants::BALL_Y_POS,
			GameConstants::BALL_RADIUS,
			GameConstants::BALL_SPEED_X,
			GameConstants::BALL_SPEED_Y,
			GameConstants::BALL_COLOR
		);

		Paddle leftPaddle(
			GameConstants::LEFT_PADDLE_X_POS,
			GameConstants::PADDLE_Y_POS,
			GameConstants::PADDLE_SPEED,
			GameConstants::PADDLE_WIDTH,
			GameConstants::PADDLE_HEIGHT
		);

		Paddle rightPaddle(
			GameConstants::RIGHT_PADDLE_X_POS,
			GameConstants::PADDLE_Y_POS,
			GameConstants::PADDLE_SPEED,
			GameConstants::PADDLE_WIDTH,
			GameConstants::PADDLE_HEIGHT
		);

		const char* winnerText = nullptr;
		int leftPlayerScore = 0;
		int rightPlayerScore = 0;


		while (!WindowShouldClose()) {
			ball.xPos += ball.speedX * GetFrameTime();
			ball.yPos += ball.speedY * GetFrameTime();

			//Detecting ball colision with top and bottom part of the window
			if (ball.yPos < 0) {
				ball.yPos = 0;
				ball.speedY *= -1;
			}

			if (ball.yPos > GetScreenHeight()) {
				ball.yPos = GetScreenHeight();
				ball.speedY *= -1;
			}

			//Move paddles
			if (!winnerText) {
				if (IsKeyDown(KEY_W) && leftPaddle.yPos - leftPaddle.height / 2 > 0) {
					leftPaddle.yPos -= leftPaddle.speed * GetFrameTime();
				}

				if (IsKeyDown(KEY_S) && leftPaddle.yPos < GetScreenHeight()) {
					leftPaddle.yPos += leftPaddle.speed * GetFrameTime();
				}

				if (IsKeyDown(KEY_UP) && rightPaddle.yPos - rightPaddle.height / 2 > 0) {
					rightPaddle.yPos -= rightPaddle.speed * GetFrameTime();
				}

				if (IsKeyDown(KEY_DOWN) && rightPaddle.yPos < GetScreenHeight()) {
					rightPaddle.yPos += rightPaddle.speed * GetFrameTime();
				}
			}

			//Detect ball colision with paddles & block infinite hits
			if (CheckCollisionCircleRec(Vector2{ ball.xPos, ball.yPos }, ball.radius, leftPaddle.GetRect())) {
				if (ball.speedX < 0) {
					ball.speedX *= -1.25f;
					ball.speedY = (ball.yPos - leftPaddle.yPos) / (leftPaddle.height / 2) * ball.speedX;
				}
			}

			if (CheckCollisionCircleRec(Vector2{ ball.xPos, ball.yPos }, ball.radius, rightPaddle.GetRect())) {
				if (ball.speedX > 0) {
					ball.speedX *= -1.25f;
					ball.speedY = (ball.yPos - rightPaddle.yPos) / (rightPaddle.height / 2) * ball.speedX * -1;
				}
			}

			if (ball.xPos < 0) {
				winnerText = GameConstants::WINNER_TEXT_RIGHT_PLAYER.c_str();
			}

			if (ball.xPos > GetScreenWidth()) {
				winnerText = GameConstants::WINNER_TEXT_LEFT_PLAYER.c_str();
			}

			if (winnerText && IsKeyPressed(KEY_SPACE)) {
				if (winnerText == GameConstants::WINNER_TEXT_RIGHT_PLAYER.c_str()) rightPlayerScore++;

				if (winnerText == GameConstants::WINNER_TEXT_LEFT_PLAYER.c_str()) leftPlayerScore++;;

				x->saveToFile(1, 2);

				ball.xPos = GameConstants::BALL_X_POS;
				ball.yPos = GameConstants::BALL_Y_POS;
				ball.speedX = GameConstants::BALL_SPEED_X;
				ball.speedY = GameConstants::BALL_SPEED_Y;;
				rightPaddle.yPos = GameConstants::PADDLE_Y_POS;
				leftPaddle.yPos = GameConstants::PADDLE_Y_POS;
				
				winnerText = nullptr;

			}

			BeginDrawing();
			ClearBackground(GameConstants::BACKGROUND_COLOR);

			ball.Draw();
			//Left Padle Rectangle
			leftPaddle.Draw();
			//Right Padle Rectangle
			rightPaddle.Draw();

			if (winnerText) {
				int textWidth = MeasureText(winnerText, 60);
				DrawText(winnerText, GetScreenWidth() / 2 - (textWidth / 2), GetScreenHeight() / 2 - 30, 60, GameConstants::WINNER_COLOR);
			}

			DrawText(std::to_string(leftPlayerScore).c_str(), GetScreenWidth() / 4, 20, 60, BLACK);
			DrawText(std::to_string(rightPlayerScore).c_str(), GetScreenWidth() - GetScreenWidth() / 4, 20, 60, BLACK);

			DrawFPS(10, 10);
			EndDrawing();
		}

		delete x;
		CloseWindow();

		return 0;
	}
};
