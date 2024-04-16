#include "raylib.h"
#include <math.h>
#include "linear_search.h"
// Define the different screens
typedef enum { MAIN_MENU, MENU,ALGORITHM_TYPE,SEARCHING_SELECTOR } Screen;

typedef struct Button
{
    Rectangle rect;
    Color color;
    char *text;
    Color textColor;

} Button;

Button button_1;
Button button_2;
Button button_sorting;
Button button_searching;

Button linear_search;
Button binary_search;

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
void RenderAlgorithmTypeSelection()
{
    ClearBackground(RAYWHITE);
    DrawText("Select Option", 400, 0, 50, LIGHTGRAY);
  

    // Render button 1
      DrawRectangleRec(button_sorting.rect, button_sorting.color);
    DrawText(button_sorting.text, button_sorting.rect.x + button_sorting.rect.width / 2 - MeasureText(button_sorting.text, 20) / 2, button_sorting.rect.y + button_sorting.rect.height / 2 - 20 / 2, 20, button_sorting.textColor);


    // Render button 2
    DrawRectangleRec(button_searching.rect, button_searching.color); 
    DrawText(button_searching.text, button_searching.rect.x + button_searching.rect.width / 2 - MeasureText(button_searching.text, 20) / 2, button_searching.rect.y + button_searching.rect.height / 2 - 20 / 2, 20, button_searching.textColor);
}

void RenderSearchingSelector(){
    ClearBackground(RAYWHITE);
    DrawText("Select Algorithm", 400, 0, 50, LIGHTGRAY);
  

    // Render button 1
    DrawRectangleRec(linear_search.rect, linear_search.color);
    DrawText(linear_search.text, linear_search.rect.x + linear_search.rect.width / 2 - MeasureText(linear_search.text, 20) / 2, linear_search.rect.y + linear_search.rect.height / 2 - 20 / 2, 20, linear_search.textColor);

    // Render button 2
    DrawRectangleRec(binary_search.rect, binary_search.color);
    DrawText(binary_search.text, binary_search.rect.x + binary_search.rect.width / 2 - MeasureText(binary_search.text, 20) / 2, binary_search.rect.y + binary_search.rect.height / 2 - 20 / 2, 20, binary_search.textColor);

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
    init_button(&button_searching,(Rectangle){550,60,400,400},LIGHTGRAY,"Searching-Algorithm",RED);
    init_button(&button_sorting, (Rectangle){50, 60, 400, 400}, LIGHTGRAY, "Sorting-Algorithm", RED);
    init_button(&linear_search,(Rectangle){50,60,400,400},LIGHTGRAY,"Linear-Search",RED);
    init_button(&binary_search,(Rectangle){550,60,400,400},LIGHTGRAY,"Binary-Search",RED);
    Screen currentScreen = MAIN_MENU;

    while (!WindowShouldClose())
    {
        // Update
        switch (currentScreen)
        {
        case MAIN_MENU:
            if (is_mouse_over_button(button_1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = ALGORITHM_TYPE;
            }
            else if (is_mouse_over_button(button_2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = MENU;
            }
            break;
        case MENU:
            // Handle menu logic here
            break;
        case ALGORITHM_TYPE:
            if(IsKeyPressed(KEY_BACKSPACE)){
                    currentScreen = MAIN_MENU;
             }
            if(is_mouse_over_button(button_searching) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                    currentScreen = SEARCHING_SELECTOR;
            }
            break;
        case SEARCHING_SELECTOR:
                if(is_mouse_over_button(linear_search) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                    runLinearSearchVisualizer();
                }
              if(IsKeyPressed(KEY_BACKSPACE)){
                    currentScreen = ALGORITHM_TYPE;
             }
            break;
        default:
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
        case ALGORITHM_TYPE:
            RenderAlgorithmTypeSelection();
            break;
        case SEARCHING_SELECTOR:
            RenderSearchingSelector();
            break;
        default:
            break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
