#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include "main.h"
#include <raygui/raygui.h>
#include <raylib.h>
#include <stack>
#include "linear_search.h"
#include "array.h"
screen currentscreen;
std::stack<screen> screenStack;

#define screenWidth 800
#define screenHeight 600

float scaling_factorX = 1.0f;
float scaling_factorY = 1.0f;

void RenderMainScreen(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

  
    const char* title_text  = "Algolizer";
    const float button_width = 250;
    const float button_height = 70; 

    const int gap = 100*scaling_factorY;

  
    const float X_Position = ((screenWidth/2.0) - (button_width/2.0)) * scaling_factorX;
    const float Y_Position = ((screenHeight/2.0) - button_height) * scaling_factorY;
        


    Rectangle button_Algo = {X_Position,Y_Position,button_width*scaling_factorX,button_height*scaling_factorY};
    Rectangle button_DataS = {X_Position,Y_Position+gap,button_width*scaling_factorX,button_height*scaling_factorY};

    
       
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(title_text, X_Position+35, 30, 50 * scaling_factorX, GRAY);



    bool isAlgorithmPressed = GuiButton(button_Algo,"Algorithms");
    bool isDataStructurePressed = GuiButton(button_DataS,"Data-Structures");

    screenStack.push(currentscreen);

    if(isAlgorithmPressed){

        currentscreen = ALGORITHM_LIST; 


    }
    if(isDataStructurePressed){
        currentscreen = DATASTRUCTURE_LIST;

    }

    EndDrawing();
}


void RenderAlgorithmList(){
   const float buttonWidth = 350;
    const float buttonHeight = 50;
    const float margin = 20;
    const float col1X = margin;
    const float col2X = screenWidth / 2.0 + margin;
    float yPos = margin;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20); 
    GuiGroupBox(Rectangle{ col1X, yPos, buttonWidth, screenHeight - 2 * margin }, "Sorting");
    GuiButton(Rectangle{ col1X + margin, yPos + 2 * margin, buttonWidth - 2 * margin, buttonHeight }, "Bubble Sort");
    GuiButton(Rectangle{ col1X + margin, yPos + 2 * margin + buttonHeight + margin, buttonWidth - 2 * margin, buttonHeight }, "Merge Sort");
    GuiButton(Rectangle{ col1X + margin, yPos + 2 * margin + 2 * (buttonHeight + margin), buttonWidth - 2 * margin, buttonHeight }, "Selection Sort");
    GuiButton(Rectangle{ col1X + margin, yPos + 2 * margin + 3 * (buttonHeight + margin), buttonWidth - 2 * margin, buttonHeight }, "Quick Sort");
    GuiButton(Rectangle{ col1X + margin, yPos + 2 * margin + 4 * (buttonHeight + margin), buttonWidth - 2 * margin, buttonHeight }, "Insertion Sort");

    // Draw the Searching column
    GuiGroupBox(Rectangle{ col2X, yPos, buttonWidth, screenHeight - 2 * margin }, "Searching");
    bool linearSearch = GuiButton(Rectangle{ col2X + margin, yPos + 2 * margin, buttonWidth - 2 * margin, buttonHeight }, "Linear Search");
    GuiButton(Rectangle{ col2X + margin, yPos + 2 * margin + buttonHeight + margin, buttonWidth - 2 * margin, buttonHeight }, "Binary Search");

    if(linearSearch){
        screenStack.push(currentscreen);
        currentscreen = LINEARSEARCH;
    }


    EndDrawing();


}


void RenderDataStructureList(){

    const float buttonWidth = 280;
    const float buttonHeight = 60;
    const float margin = 50;

    float xPos = margin;
    float yPos = margin;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20); 
    // Draw the Data Structures group box
    GuiGroupBox(Rectangle{ xPos, yPos, screenWidth - 2 * margin, screenHeight - 2 * margin }, "Data Structures");

    // Draw the buttons
    bool arrayVisualizer = GuiButton(Rectangle{ xPos + margin, yPos + 2 * margin, buttonWidth, buttonHeight }, "Array");
    GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * margin, buttonWidth, buttonHeight }, "Stack");
    GuiButton(Rectangle{ xPos + margin, yPos + 2 * margin + buttonHeight + margin, buttonWidth, buttonHeight }, "Queue");
    GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * margin + buttonHeight + margin, buttonWidth, buttonHeight }, "Tree");
    GuiButton(Rectangle{ xPos + margin, yPos + 2 * margin + 2 * (buttonHeight + margin), buttonWidth, buttonHeight }, "Graph");
    GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * margin + 2 * (buttonHeight + margin), buttonWidth, buttonHeight }, "Linked List");


    if(arrayVisualizer){
        screenStack.push(currentscreen);
        currentscreen = ARRAY_VISUALIZER;
    }

    EndDrawing();
}




int main(){
   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Algolizer");
    SetWindowMinSize(screenWidth, screenHeight);
    SetTargetFPS(60);

    currentscreen = MAINSCREEN;


    while(!WindowShouldClose()){

        if(IsWindowResized()){
            scaling_factorX = static_cast<double> (GetScreenWidth()) / static_cast<double>(screenWidth);
            scaling_factorY = static_cast<double> (GetScreenHeight()) / static_cast<double>(screenHeight);
        }
        
        switch(currentscreen){
            case MAINSCREEN:
                RenderMainScreen();
                break;
            case ALGORITHM_LIST:
                RenderAlgorithmList();
                break;
            case DATASTRUCTURE_LIST:
                RenderDataStructureList();
                break;
            case LINEARSEARCH:
                runLinearSearchVisualizer();
                break;
            case ARRAY_VISUALIZER:
                runArrayVisualizer();
                break;
            default:
                break;

        }

        if(IsKeyPressed(KEY_B)){

            if(!screenStack.empty()){
                currentscreen =screenStack.top();
                screenStack.pop();
            }
        } 
    }


    CloseWindow();
    return 0;
}
