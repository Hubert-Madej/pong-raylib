module;
#include "raylib.h"
export module gameManager;
import constants;
import game;

export struct GameManager
{
	int start() {

        // Initialize the window
        InitWindow(GameConstants::GAME_WINDOW_WIDTH, GameConstants::GAME_WINDOW_HEIGHT, GameConstants::GAME_WINDOW_TITLE.c_str());
        SetWindowState(FLAG_VSYNC_HINT);
        SetExitKey(0);

        // Define the button rectangles
        int buttonWidth = 400;
        int buttonHeight = 80;
        Rectangle playButton = { GameConstants::GAME_WINDOW_WIDTH / 2 - buttonWidth / 2, 180, buttonWidth, buttonHeight };
        Rectangle historyButton = { GameConstants::GAME_WINDOW_WIDTH / 2 - buttonWidth / 2, 280, buttonWidth, buttonHeight };
        Rectangle exitButton = { GameConstants::GAME_WINDOW_WIDTH / 2 - buttonWidth / 2, 380, buttonWidth, buttonHeight };

        // Define the button state variables
        bool playPressed = false;
        bool historyPressed = false;
        bool exitPressed = false;

        Font font = GetFontDefault();
        int fontSize = 40;

        // Main game loop
        while (!WindowShouldClose())
        {
            // Check if the play button is pressed
            if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                playPressed = true;
            }

            // Check if the settings button is pressed
            if (CheckCollisionPointRec(GetMousePosition(), historyButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                historyPressed = true;
            }

            // Check if the exit button is pressed
            if (CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                exitPressed = true;
            }

            // Draw the menu
            BeginDrawing();
            ClearBackground(GameConstants::BACKGROUND_COLOR);

            DrawText("Main Menu", GameConstants::GAME_WINDOW_WIDTH / 2 - MeasureText("Main Menu", 40) / 2, 80, 40, BLACK);

            DrawRectangleRec(playButton, playPressed ? LIGHTGRAY : WHITE);
            DrawText("Play", playButton.x + playButton.width / 2 - MeasureText("Play", fontSize) / 2, playButton.y + playButton.height / 2 - fontSize / 2, fontSize, BLACK);

            DrawRectangleRec(historyButton, historyPressed ? LIGHTGRAY : WHITE);
            DrawText("Games History", historyButton.x + historyButton.width / 2 - MeasureText("Games History", fontSize) / 2, historyButton.y + buttonHeight / 2 - fontSize / 2, fontSize, BLACK);

            DrawRectangleRec(exitButton, exitPressed ? LIGHTGRAY : WHITE);
            DrawText("Exit", exitButton.x + exitButton.width / 2 - MeasureText("Exit", fontSize) / 2, exitButton.y + exitButton.height / 2 - fontSize / 2, fontSize, BLACK);

            EndDrawing();

            // Check the button state variables and take appropriate actions
            if (playPressed)
            {
                // Call the PlayGame function to start the game
                Game g;
                g.start();

                // Reset the button state variables
                playPressed = false;
                historyPressed = false;
                exitPressed = false;
            }
            else if (historyPressed)
            {
                // Open the settings menu
                break;
            }
            else if (exitPressed)
            {
                // Exit the main menu loop and close the window
                break;
            }
        }

        // Close the window
        CloseWindow();

        return 0;
    }
};