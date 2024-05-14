#include <chrono>
#include <raylib.h>
#include "bubble_sort.h"
#include "main.h"
#include <iostream>
#include <stack>
#include <thread>
#include <vector>
int bar_width = 20;
int comparision_count = 0;
extern std::stack<screen> screenStack;
extern screen currentscreen;

void DrawState(const std::vector<int>& dataset, int currentElement, int comparisionElement){
    const int bar_gap = bar_width+1;
    DrawText(TextFormat("Sample Size : %d ",dataset.size()),20,20,15,BLACK);
    DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
    
    BeginDrawing();
    ClearBackground(RAYWHITE); 
    int startingX = 2;
    for(int i=0;i<dataset.size();i++){  
        Color baseColor = BLACK;
        if(i == currentElement){
            baseColor = BLUE;
        }else if(i == comparisionElement){
            baseColor = RED;
        }
        DrawRectangle(startingX,GetScreenHeight()-dataset[i],bar_width,dataset[i],baseColor);
        startingX += bar_gap;
    }
    EndDrawing();
}





void RunBubbleSortVisualizer(){
    const int max_barHeight = GetScreenHeight()-100;
    const int min_barHeight = 20; 
    const int bar_count = GetScreenWidth()/(bar_width+1);

 
   SetTargetFPS(144); // Change This Value To Increase Animation Time 


    std::vector<int> dataset; 
    for(int i =0;i<bar_count;i++){
        dataset.push_back(GetRandomValue(min_barHeight, max_barHeight));
    }
    bool isSorted = false;
  
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_B)){
           currentscreen = screenStack.top();
           break;
        }

        if(!isSorted){
            for(int i = 0;i<dataset.size()-1;i++){
                for(int j = 0;j<dataset.size()-i-1;j++){
                    if(dataset[j] > dataset[j+1]){
                        std::swap(dataset[j],dataset[j+1]);
                    }
                    comparision_count++; 
                    DrawState(dataset,j,j+1);
                }
            }
           isSorted = true;
        }
       
        DrawState(dataset,-1,-1); // -1 to indicate sorted , can render using black color;

        // Drawing Bars    
    
    }
    comparision_count = 0;
    

}
    


