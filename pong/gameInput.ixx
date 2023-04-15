module;
#include "raylib.h"
#include <string>
export module gameInput;
import constants;

export struct GameInput
{
    std::string displayInput(std::string &s) {
        const int MAX_INPUT_CHARS = 9;
        char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
        int letterCount = 0;
        std::string username;

        int buttonWidth = 225;
        int buttonHeight = 50;
        Rectangle submitButton = { GameConstants::GAME_WINDOW_WIDTH / 2 - buttonWidth / 2 + 10, 240, buttonWidth, buttonHeight };
        bool submitButtonClicked = false;

        Rectangle textBox = { GameConstants::GAME_WINDOW_WIDTH / 2.0f - 100, 180, 225, 50 };
        bool mouseOnText = false;

        int framesCounter = 0;
      
        while (!WindowShouldClose())    
        {
            if (CheckCollisionPointRec(GetMousePosition(), textBox)) SetMouseCursor(MOUSE_CURSOR_IBEAM);
            else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                mouseOnText = true;
            }

            if (mouseOnText)
            {
                // Get char pressed (unicode character) on the queue
                int key = GetCharPressed();

                // Check if more characters have been pressed on the same frame
                while (key > 0)
                {
                    // NOTE: Only allow keys in range [32..125]
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                    {
                        name[letterCount] = (char)key;
                        name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                        letterCount++;
                    }
                    int name_size = sizeof(name) / sizeof(char);
                    username = convertToString(name, name_size);

                    key = GetCharPressed();  // Check next character in the queue
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    name[letterCount] = '\0';
                }

                if (CheckCollisionPointRec(GetMousePosition(), submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    submitButtonClicked = true;
                    mouseOnText = false;

                    if (username.length() > 0) return username;
                }
            }
            else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (mouseOnText) framesCounter++;
            else framesCounter = 0;
            BeginDrawing();

            ClearBackground(GameConstants::BACKGROUND_COLOR);
            DrawRectangleRec(submitButton, WHITE);
            DrawText("Submit", submitButton.x + submitButton.width / 2 - MeasureText("Submit", 20) / 2, submitButton.y + submitButton.height / 2 - 20 / 2, 20, BLACK);

            int textWidth = MeasureText("Enter Winner Name:", 30);
            DrawText("Enter Winner Name:", GetScreenWidth() / 2 - (textWidth / 2), 120, 30, GameConstants::WINNER_COLOR);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
            }
            EndDrawing();
        }
 
        CloseWindow();        

        return username;
    }

    std::string convertToString(char* a, int size)
    {
        int i;
        std::string s = "";
        for (i = 0; i < size; i++) {
            s = s + a[i];
        }
        return s;
    }
};