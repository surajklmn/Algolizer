#include "main.h"
#include "raylib.h"
#include <chrono>
#include <thread>
#include <stack>
#include "selection_sort.h"
const int screen_width = 800;
const int screen_height = 600;
const int bar_width = 20;
const int numBars = screen_width/bar_width;
extern std::stack<screen> screenStack;
extern screen currentscreen;
void swap(int &x, int  &y){
    int temp = x;
    x = y;
    y =  temp;
}
void selectionVisualizer(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        int min_index = i;
        for(int j = i + 1; j < n; j++){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            for(int k = 0; k < numBars; k++){
                if(k == i || k == j){
                    DrawRectangle((k*bar_width) + 2, screen_height - arr[k], bar_width, arr[k], RED);

                }
                else{

                    DrawRectangle((k*bar_width)+2,screen_height - arr[k], bar_width, arr[k], BLACK);
                }

            }
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if(arr[j] < arr[min_index] ){
                min_index = j; 

            }
        }


        swap(arr[min_index],arr[i]);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for(int k = 0; k < numBars; k++){
            if(k == i || k == min_index){
                DrawRectangle((k * bar_width) + 2, screen_height - arr[k], bar_width,arr[k],GREEN);
            }

            else{
                DrawRectangle((k* bar_width) + 2, screen_height - arr[k], bar_width,arr[k], BLACK);
            }
        }
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
void RunSelectionSortVisualizer(){

    SetTargetFPS(60);
    int data[numBars];
    for(int i = 0; i < numBars; i++){
        data[i] = GetRandomValue(10, screen_height-20);

    }
    bool isSorted = false;

    const int bar_gap = bar_width + 1;
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        if(IsKeyPressed(KEY_B)){
            currentscreen = screenStack.top();
            break;

        }
        if(!isSorted){
            selectionVisualizer(data, numBars);
            isSorted = true;
        }

        BeginDrawing();


        ClearBackground(RAYWHITE);

        int posX = 2;
        for(int i = 0; i < numBars; i++){
            DrawRectangle(i*bar_width, GetScreenHeight() - data[i], bar_width, data[i], BLACK);

        }



        EndDrawing(); 
    }
    CloseWindow();

}

