#include "main.h"
#include "raylib.h"
#include <chrono>
#include <thread>
#include <stack>
#include "insertion_sort.h"
int screen_width;
int screen_height;
const int bar_width = 20;
int numBars;
const int gap = 1;
extern std::stack<screen> screenStack;
extern screen currentscreen;
extern int comparision_count;
void insertionVisualizer(std::vector<int>& arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Visualize the key being compared
        while (j >= 0 && arr[j] > key) {
            comparision_count++;
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Sample Size : %d ",arr.size()),20,20,15,BLACK);
            DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
            for (int k = 0; k < numBars; k++) {
                if (k == j + 1) {
                    DrawRectangle(k * (bar_width + gap), screen_height - arr[k], bar_width, arr[k], RED);
                } else if (k == j) {
                    DrawRectangle(k * (bar_width + gap), screen_height - arr[k], bar_width, arr[k], YELLOW);
                } else if (k == i) {
                    DrawRectangle(k * (bar_width + gap), screen_height - arr[k], bar_width, arr[k], BLUE);
                } else {
                    DrawRectangle(k * (bar_width + gap), screen_height - arr[k], bar_width, arr[k], BLACK);
                }
            }
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        // Visualize the array after placing the key in its correct position
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Sample Size : %d ",arr.size()),20,20,15,BLACK);
        DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
        for (int k = 0; k < numBars; k++) {
            if (k <= i) {
                DrawRectangle(k * (bar_width + gap), screen_height - arr[k], bar_width, arr[k], GREEN);
            } else {
                DrawRectangle(k * (bar_width + gap), screen_height - arr[k], bar_width, arr[k], BLACK);
            }
        }
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void RunInsertionSortVisualizer() {
    comparision_count  =0;
    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();
    numBars = screen_width / (bar_width+gap);

    SetTargetFPS(60);

    std::vector<int> data(numBars);
    for (int i = 0; i < numBars; i++) {
        data[i] = GetRandomValue(10, screen_height - 20);
    }
    bool isSorted = false;

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
         if(IsWindowResized()){
            CalculateScalingFactor(); 
        }
        if (IsKeyPressed(KEY_B)) {
            currentscreen = screenStack.top();
            break;
        }
        if (!isSorted) {
            insertionVisualizer(data, numBars);
            isSorted = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Sample Size : %d ",data.size()),20,20,15,BLACK);
        DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);
        for (int i = 0; i < numBars; i++) {
            DrawRectangle(i * (bar_width + gap), GetScreenHeight() - data[i], bar_width, data[i], BLACK);
        }

        EndDrawing();
    }
}

