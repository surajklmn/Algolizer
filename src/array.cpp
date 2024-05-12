#include <iostream>
#include <random>
#include <raylib.h>
#include <raygui/raygui.h>
#include <string>
#include <vector>
#include <stack>
#include "array.h"
#include "main.h"
#include "utils/InputBox.h"
enum calledBy{
    SELECT,
    REMOVE,
    UPDATE,
}called;

extern std::stack<screen> screenStack;
extern screen currentscreen;

void runArrayVisualizer(){
    int array_size = 10;
    int box_width = 50;
    int box_height = 50; 
    int selectedIndex = -1;
    int removeIndex;
    int updateIndex;
    std::vector<int> dataset;   
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (int i = 0; i < array_size; i++) {
        dataset.push_back(0);
    }
    InputBox data_input({static_cast<float>(GetScreenWidth()/2.0)-100,100,180,40}); 
    while(!WindowShouldClose()){
        int box_gap = 10;
        int startingX = 100;
        int startingY = GetScreenHeight()/2;
    

        BeginDrawing();

        bool selectElement = GuiButton({50,30,200,40},"Select Index");
        bool updateElement = GuiButton({300,30,200,40},"Update At Index");
        bool removeElement =  GuiButton({550,30,200,40},"Remove At Index");
        if(IsKeyPressed(KEY_B)){
            
        }
        
        if(selectElement || (called == SELECT && data_input.IsEnteringInput() && IsKeyPressed(KEY_ENTER))){  
            called = SELECT;
            data_input.Update();
            
            if(!data_input.IsEnteringInput()){
                selectedIndex = data_input.GetInputValue();
            }

        }
         if(updateElement || (called== UPDATE && data_input.IsEnteringInput() && IsKeyPressed(KEY_ENTER))){  
            called = UPDATE;
            data_input.Update();
            
            if(!data_input.IsEnteringInput()){
                updateIndex = data_input.GetInputValue();
                dataset[updateIndex] = dis(gen);
            }

        }
        if(removeElement || (called == REMOVE && data_input.IsEnteringInput() && IsKeyPressed(KEY_ENTER))){  
            called = REMOVE;
            data_input.Update();
            
            if(!data_input.IsEnteringInput()){
                removeIndex = data_input.GetInputValue();
                dataset[removeIndex] = 0;   
            }
            
        }
     
        if (IsKeyPressed(KEY_B)) {
            currentscreen = screenStack.top();
            break;
        }


        if(data_input.IsEnteringInput()){
            data_input.Draw();
        }
        ClearBackground(RAYWHITE); 
        DrawText("Index -> ",20,startingY-70, 20, BLACK);
        Color color = BLACK;
        for(int i=0;i<dataset.size();i++){

            
           if(selectedIndex == i) color = DARKGREEN;
             DrawRectangle(startingX+box_gap,startingY-30,box_width,box_height,color);
            DrawText(TextFormat("%d",i),startingX+(box_width/2-5),startingY-70,20,BLACK); 
            DrawText(TextFormat("%i",dataset[i]),startingX+(box_width/2-5),startingY+(box_height/2)-30,20,WHITE);
            
            startingX = startingX+box_gap+box_width;
            color = BLACK;
        }
    
    

        EndDrawing();
    }






}
