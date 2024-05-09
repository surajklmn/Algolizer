#include <iostream>
#include <random>
#include <raylib.h>
#include <raygui/raygui.h>
#include <string>
#include <vector>
#include "array.h"
#include "utils/InputBox.h"


void runArrayVisualizer(){
    int array_size = 10;
    int box_width = 60;
    int box_height = 60; 
    int selectedIndex;
    std::vector<int> dataset;   
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (int i = 0; i < array_size; i++) {
        dataset.push_back(dis(gen));
    }
    InputBox data_input({static_cast<float>(GetScreenWidth()/2.0)-100,100,180,40}); 
    while(!WindowShouldClose()){
        int box_gap = 10;
        int startingX = 50;
        int startingY = GetScreenHeight()/2;
    

        BeginDrawing();

        bool selectElement = GuiButton({50,30,160,40},"Select Element");
        bool updateElement = GuiButton({230,30,160,40},"Update Element");
        bool insertElement =  GuiButton({410,30,160,40},"Insert Element");
        bool removeElement =  GuiButton({590,30,160,40},"Remove Element");

        
        if(selectElement || (data_input.IsEnteringInput() && IsKeyPressed(KEY_ENTER))){  
            data_input.Update();
            
            if(!data_input.IsEnteringInput()){
                selectedIndex = data_input.GetInputValue();
            }

        }
             if(data_input.IsEnteringInput()){
            data_input.Draw();
        }
        ClearBackground(RAYWHITE); 

        Color color = BLACK;
        for(int i=0;i<dataset.size();i++){
           if(selectedIndex == i) color = DARKGREEN;
             DrawRectangle(startingX+box_gap,startingY-30,box_width,box_height,color);
            
            DrawText(TextFormat("%i",dataset[i]),startingX+(box_width/2-5),startingY+(box_height/2)-30,20,WHITE);
            
            startingX = startingX+box_gap+box_width;
            color = BLACK;
        }
    
    

        EndDrawing();
    }






}
