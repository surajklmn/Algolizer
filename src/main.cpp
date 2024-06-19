#ifndef __APPLE__
#define RAYGUI_IMPLEMENTATION
#include "linked_list.hpp"
#endif // !__APPLE__
#include "linked_list.hpp"
#include "bubble_sort.h"
#include "merge_sort.hpp"
#include <iostream>
#include "bubble_sort.h"
#include "main.h"
#include <raygui/raygui.h>
#include <raylib.h>
#include <stack>
#include "binary_search.h"
#include "linear_search.h"
#include "array.h"
#include "queue.h"
#include "stack.h"
#include "selection_sort.h"
#include "tree.hpp"
#include "insertion_sort.h"
#include "quick_sort.hpp"
#include "graph.h"
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

    DrawText(title_text, (X_Position+35), 30 * scaling_factorY, 50 * scaling_factorX, GRAY);

    bool isAlgorithmPressed = GuiButton(button_Algo,"Algorithms");
    bool isDataStructurePressed = GuiButton(button_DataS,"Data-Structures");



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
    const float BasebuttonWidth = 360;
    const float BasebuttonHeight = 50;
    const float buttonWidth = BasebuttonWidth * scaling_factorX;
    const float buttonHeight = BasebuttonHeight * scaling_factorY;
    const float margin = 20 * scaling_factorX;
    const float col1X = 40 * scaling_factorX;
    const float col2X = (screenWidth / 2.0 + 20)*scaling_factorX;
    const float outlineHeight = (screenHeight - 40)*scaling_factorY;
    const float buttonHeightMargin = (BasebuttonHeight+20);
    const float yPos = 20;

    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);



    GuiGroupBox(Rectangle{ margin, yPos, buttonWidth, outlineHeight }, "Sorting");
    bool bubbleSort = GuiButton(Rectangle{ col1X, (yPos + 40)*scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Bubble Sort");
    bool mergesort =  GuiButton(Rectangle{ col1X, (yPos + 40 + buttonHeightMargin)*scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Merge Sort"); 
    bool selectionSort =  GuiButton(Rectangle{ col1X, (yPos + 40 + 2 * buttonHeightMargin)*scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Selection Sort");
    bool quickSort = GuiButton(Rectangle{ col1X, (yPos + 40 + 3 * buttonHeightMargin)*scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Quick Sort");
   bool insertionSort =  GuiButton(Rectangle{ col1X, (yPos + 40 + 4 * buttonHeightMargin)*scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Insertion Sort");

    // Draw the Searching column
    GuiGroupBox(Rectangle{ col2X, yPos, buttonWidth, outlineHeight }, "Searching");
    bool linearSearch = GuiButton(Rectangle{ col2X + margin, (yPos + 40) * scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Linear Search");
    bool binarySearch = GuiButton(Rectangle{ col2X + margin, (yPos + 40 + buttonHeightMargin)*scaling_factorY, buttonWidth - 2 * margin, buttonHeight }, "Binary Search");

    if(linearSearch){
        screenStack.push(currentscreen);
        currentscreen = LINEARSEARCH;
    }
    else if(binarySearch){
        screenStack.push(currentscreen);
        currentscreen = BINARYSEARCH;
    }else if(bubbleSort){
        screenStack.push(currentscreen);
        currentscreen = BUBBLESORT_VISUALIZER;
    }else if(mergesort){
        screenStack.push(currentscreen);
        currentscreen = MERGESORT_VISUALIZER;
    }
    else if(selectionSort){
    screenStack.push(currentscreen);
        currentscreen = SELECTIONSORT_VISUALIZER;
    }
    else if(insertionSort){
    screenStack.push(currentscreen);
        currentscreen = INSERTIONSORT_VISUALIZER;
    }else if(quickSort){
         screenStack.push(currentscreen);
        currentscreen = QUICKSORT_VISUALIZER;

    }
    EndDrawing();
}
void RenderDataStructureList(){

    const float BasebuttonWidth = 280;
    const float BasebuttonHeight = 60;

    const float buttonWidth = BasebuttonWidth * scaling_factorX;
    const float buttonHeight = BasebuttonHeight * scaling_factorY;

    const float margin = 50 * scaling_factorX;
    const float marginY = 50 * scaling_factorY;

    float xPos = 50 * scaling_factorX;
    float yPos = 50 * scaling_factorY;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20); 
    // Draw the Data Structures group box
    GuiGroupBox(Rectangle{ xPos, yPos, (screenWidth - 100) * scaling_factorX, (screenHeight - 100)* scaling_factorY }, "Data Structures");

    // Draw the buttons
    bool arrayVisualizer = GuiButton(Rectangle{ xPos + margin, yPos + 2 * marginY, buttonWidth, buttonHeight }, "Array");
    bool stackVisualizer = GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * marginY, buttonWidth, buttonHeight }, "Stack");
    bool queueVisualizer = GuiButton(Rectangle{ xPos + margin, yPos + 2 * marginY + buttonHeight + marginY, buttonWidth, buttonHeight }, "Queue");
    bool treeVisualizer = GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * marginY + buttonHeight + marginY, buttonWidth, buttonHeight }, "Tree");
    bool graphVisualizer = GuiButton(Rectangle{ xPos + margin, yPos + 2 * marginY + 2 * (buttonHeight + marginY), buttonWidth, buttonHeight }, "Graph");
    bool linkedVisualizer = GuiButton(Rectangle{ xPos + margin + buttonWidth + margin, yPos + 2 * marginY + 2 * (buttonHeight + marginY), buttonWidth, buttonHeight }, "Linked List");


    if(arrayVisualizer){
        screenStack.push(currentscreen); 
        currentscreen = ARRAY_VISUALIZER;
    }else if(queueVisualizer){
        screenStack.push(currentscreen);
        currentscreen = QUEUE_VISUALIZER;
    }else if(stackVisualizer){
        screenStack.push(currentscreen);
        currentscreen = STACK_VISUALIZER;
    }
    if(treeVisualizer){
        screenStack.push(currentscreen);
        currentscreen = TREE_VISUALIZER;

    }
    if(graphVisualizer){
        screenStack.push(currentscreen);
        currentscreen = GRAPH_VISUALIZER;

    }if(linkedVisualizer){
        screenStack.push(currentscreen);
        currentscreen = LINKEDLIST_VISUALIZER;
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
            case BINARYSEARCH:
                runBinarySearchVisualizer();
                break;
            case ARRAY_VISUALIZER:
                runArrayVisualizer();
                break;
            case QUEUE_VISUALIZER:
                RunQueueVisualizer();
                break;
            case BUBBLESORT_VISUALIZER:
                RunBubbleSortVisualizer();
                break; 
            case STACK_VISUALIZER:
                RunStackVisualizer();
                break;
            case MERGESORT_VISUALIZER:
                RunMergeSortVisualizer();
            case SELECTIONSORT_VISUALIZER:
                RunSelectionSortVisualizer();
                break;
            case TREE_VISUALIZER:
                RunTreeVisualizer();
                break;
            case INSERTIONSORT_VISUALIZER:
                RunInsertionSortVisualizer();
                break;
            case GRAPH_VISUALIZER:
                RunGraphVisualizer();
                break;
            case QUICKSORT_VISUALIZER:
                RunQuickSortVisualizer();
                break;
            case LINKEDLIST_VISUALIZER:
                RunLinkedListVisualizer();
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
