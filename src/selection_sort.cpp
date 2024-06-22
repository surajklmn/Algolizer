#include "main.h"
#include "raylib.h"
#include <chrono>
#include <thread>
#include <stack>
#include "selection_sort.h"
//int screen_width;
//int screen_height;
const int bar_width = 20;
//int numBars;
const int gap = 1;
extern int comparision_count;
extern std::stack<screen> screenStack;
extern screen currentscreen;
void swap(int &x, int  &y){
    int temp = x;
    x = y;
    y =  temp;
}
void selectionVisualizer(std::vector<int>& arr, int n){
 
    for(int i = 0; i < n - 1; i++){
        int min_index = i;
        for(int j = i + 1; j < n; j++){
            BeginDrawing();
             DrawText(TextFormat("Sample Size : %d ",arr.size()),20,20,15,BLACK);
             DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
            ClearBackground(RAYWHITE);
            for(int k = 0; k < numBars; k++){
                if(k == i){
                    DrawRectangle(k*(bar_width+gap), screen_height - arr[k], bar_width, arr[k], YELLOW);

                }
                else if(k == j){
                        DrawRectangle(k*(bar_width+gap), screen_height - arr[k], bar_width, arr[k], RED);

                }
                
                else{

                    DrawRectangle(k*(bar_width+gap),screen_height - arr[k], bar_width, arr[k], BLACK);
                }

            }
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            comparision_count++;
            if(arr[j] < arr[min_index] ){
                min_index = j;
              

            }
        }


        swap(arr[min_index],arr[i]);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Sample Size : %d ",arr.size()),20,20,15,BLACK);
        DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
        for(int k = 0; k < numBars; k++){
            if(k == i){
                DrawRectangle(k *(bar_width + gap), screen_height - arr[k], bar_width,arr[k],GREEN);
            }
            else if (k == min_index) {
DrawRectangle(k *(bar_width + gap), screen_height - arr[k], bar_width,arr[k],YELLOW);

            
            }

            else{
                DrawRectangle(k*( bar_width + gap), screen_height - arr[k], bar_width,arr[k], BLACK);
            }
        }
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
void RunSelectionSortVisualizer(){
    comparision_count = 0;
    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();
    numBars = screen_width/(bar_width+gap);

    SetTargetFPS(60);

    std::vector<int> data(numBars);
    for(int i = 0; i < numBars; i++){
        data[i] = GetRandomValue(10, screen_height-100);

    }
    bool isSorted = false;
    const int bar_gap = bar_width + 1;
    while (!WindowShouldClose()) {
        
        ClearBackground(RAYWHITE);
        if(IsKeyPressed(KEY_B)){
            currentscreen = screenStack.top();

            break;

        }
         if(IsWindowResized()){
            CalculateScalingFactor(); 
        }
        if(!isSorted){
            selectionVisualizer(data, numBars);
            isSorted = true;
        }

        BeginDrawing();


        ClearBackground(RAYWHITE);

        int posX = 2;
        DrawText(TextFormat("Sample Size : %d ",data.size()),20,20,15,BLACK);
        DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
        for(int i = 0; i < numBars; i++){
            DrawRectangle(i*(bar_width+gap), GetScreenHeight() - data[i], bar_width, data[i], BLACK);

        }



        EndDrawing(); 
    }

}

