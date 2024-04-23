#include <iostream>
#include "main.h"
#include <raygui/raygui.h>
#include <raylib.h>
#include <stack>
#include "linear_search.h"

screen currentscreen;
std::stack<screen> screenStack;

#define screenWidth 800
#define screenHeight 600


const int button_width = 250;
const int button_height = 70;

void RenderMainScreen(){
    const int gap = 100;
    const int centerX = (screenWidth/2);
    const int centerY = screenHeight/2;
    Rectangle button_Algo = {centerX-(button_width/2.0),centerY-button_height,button_width,button_height};
    Rectangle button_DataS = {centerX-(button_width/2.0),centerY-button_height + gap,button_width,button_height};

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Algolizer",centerX-70, 30, 40, GRAY);

 
    bool isAlgorithmPressed = GuiButton(button_Algo,"Algorithm");
    bool isDataStructurePressed = GuiButton(button_DataS,"Data-Structure");
  

    if(isAlgorithmPressed){
    screenStack.push(currentscreen);
      currentscreen = ALGORITHM_LIST; 

       
    }
    if(isDataStructurePressed){
        screenStack.push(currentscreen);
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
        GuiSetStyle(DEFAULT, TEXT_SIZE, 15); 
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
        GuiSetStyle(DEFAULT, TEXT_SIZE, 15); 
        // Draw the Data Structures group box
        GuiGroupBox(Rectangle{ xPos, yPos, screenWidth - 2 * margin, screenHeight - 2 * margin }, "Data Structures");

        // Draw the buttons
        GuiButton(Rectangle{ xPos + margin, yPos + 2 * margin, buttonWidth, buttonHeight }, "Array");
        GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * margin, buttonWidth, buttonHeight }, "Stack");
        GuiButton(Rectangle{ xPos + margin, yPos + 2 * margin + buttonHeight + margin, buttonWidth, buttonHeight }, "Queue");
        GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * margin + buttonHeight + margin, buttonWidth, buttonHeight }, "Tree");
        GuiButton(Rectangle{ xPos + margin, yPos + 2 * margin + 2 * (buttonHeight + margin), buttonWidth, buttonHeight }, "Graph");
        GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * margin + 2 * (buttonHeight + margin), buttonWidth, buttonHeight }, "Linked List");
      

        EndDrawing();
}




int main(){

    InitWindow(screenWidth, screenHeight, "Algolizer");
    SetTargetFPS(60);

    currentscreen = MAINSCREEN;
 

    while(!WindowShouldClose()){
       
      
      
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
