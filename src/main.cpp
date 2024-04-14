#include "raylib.h"
#include <math.h>

// Define the different screens
typedef enum { MAIN_MENU, MENU } Screen;

typedef struct Button
{
    Rectangle rect;
    Color color;
    char *text;
    Color textColor;

} Button;

Button button_1;
Button button_2;

void init_button(Button *button, Rectangle rect, Color color, char *text, Color textColor)
{
    button->rect = rect;
    button->color = color;
    button->text = text;
    button->textColor = textColor;
}

bool is_mouse_over_button(Button button)
{
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

// Function to render the main menu screen
void RenderMainMenu()
{
    ClearBackground(RAYWHITE);
    DrawText("Algolizer", 400, 0, 50, LIGHTGRAY);
  

    // Render button 1
    DrawRectangleRec(button_1.rect, button_1.color);
    DrawText(button_1.text, button_1.rect.x + button_1.rect.width / 2 - MeasureText(button_1.text, 20) / 2, button_1.rect.y + button_1.rect.height / 2 - 20 / 2, 20, button_1.textColor);

    // Render button 2
    DrawRectangleRec(button_2.rect, button_2.color);
    DrawText(button_2.text, button_2.rect.x + button_2.rect.width / 2 - MeasureText(button_2.text, 20) / 2, button_2.rect.y + button_2.rect.height / 2 - 20 / 2, 20, button_2.textColor);
}

void RenderMenu()
{
    ClearBackground(GRAY);
    DrawText("MENU", 400, 200, 50, LIGHTGRAY);
}

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Algolizer");
    SetTargetFPS(60);

    // Initialize buttons
    init_button(&button_1, (Rectangle){50, 60, 400, 400}, LIGHTGRAY, "algorithm", RED);
    init_button(&button_2, (Rectangle){550, 60, 400, 400}, LIGHTGRAY, "Data-structure", RED);

    Screen currentScreen = MAIN_MENU;

    while (!WindowShouldClose())
    {
        // Update
        switch (currentScreen)
        {
        case MAIN_MENU:
            if (is_mouse_over_button(button_1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = MENU;
            }
            else if (is_mouse_over_button(button_2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = MENU;
            }
            break;
        case MENU:
            // Handle menu logic here
            break;
        }

        // Draw
        BeginDrawing();
        switch (currentScreen)
        {
        case MAIN_MENU:
            RenderMainMenu();
            break;
        case MENU:
            RenderMenu();
            break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
