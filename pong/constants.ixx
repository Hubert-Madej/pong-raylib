#include "string"
#include "raylib.h"
export module constants;

export struct GameConstants
{
	static const int GAME_WINDOW_HEIGHT = 800;
	static const int GAME_WINDOW_WIDTH = 1200;
	inline static const std::string GAME_WINDOW_TITLE = "Pong";

	inline static const Color BALL_COLOR = { 255, 82, 27, 255 };
	inline static const Color BACKGROUND_COLOR = { 255, 174, 62, 255 };
	inline static const Color WINNER_COLOR = { 62, 143, 255, 255 };

	inline static const float BALL_X_POS = GAME_WINDOW_WIDTH / 2.0f;
	inline static const float BALL_Y_POS = GAME_WINDOW_HEIGHT / 2.0f;
	inline static const int BALL_RADIUS = 10;
	inline static const float BALL_SPEED_X = 400;
	inline static const float BALL_SPEED_Y = 400;

	inline static const float LEFT_PADDLE_X_POS = 50.0f;

	inline static const float RIGHT_PADDLE_X_POS = GAME_WINDOW_WIDTH - 50.0f - 10.0f;
	
	inline static const float PADDLE_SPEED = 700;
	inline static const float PADDLE_WIDTH = 10;
	inline static const float PADDLE_HEIGHT = 200;
	inline static const float PADDLE_Y_POS = GAME_WINDOW_HEIGHT / 2.0f - 50.0f;

	inline static const std::string WINNER_TEXT_RIGHT_PLAYER = "Right Player Wins!";
	inline static const std::string WINNER_TEXT_LEFT_PLAYER = "Left Player Wins!";
};