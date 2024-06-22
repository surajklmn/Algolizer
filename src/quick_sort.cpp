#include "quick_sort.hpp"
#include <chrono>
#include <raylib.h>
#include <thread>
#include <vector>
#include "main.h"
#include <stack>

extern std::stack<screen> screenStack;
extern screen currentscreen;
extern int bar_width;
extern int comparision_count;



void DrawState(const std::vector<int>& arr, int low, int high, int pivot = -1) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("Sample Size : %d ",arr.size()),20,20,15,BLACK);
    DrawText(TextFormat("Comparisions : %d ",comparision_count),20,40,15,BLACK);

    for (int i = 0; i < arr.size(); i++) {
        if (i == low) {
            DrawRectangle(i * (bar_width + 1), GetScreenHeight() - arr[i], bar_width, arr[i], YELLOW);
        } else if (i == high) {
            DrawRectangle(i * (bar_width + 1), GetScreenHeight() - arr[i], bar_width, arr[i], RED);
        } else if (i == pivot) {
            DrawRectangle(i * (bar_width + 1), GetScreenHeight() - arr[i], bar_width, arr[i], GREEN);
        } else {
            DrawRectangle(i * (bar_width + 1), GetScreenHeight() - arr[i], bar_width, arr[i], BLACK);
        }
    }
    EndDrawing();
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        DrawState(arr, low, high, j);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        comparision_count++; 
        if (arr[j] < pivot) {
            i++;
           
            std::swap(arr[i], arr[j]);
            DrawState(arr, low, high, j);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    std::swap(arr[i + 1], arr[high]);
    DrawState(arr, low, high, i + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    comparision_count++;
    if (low < high) {
       
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }

}

void RunQuickSortVisualizer() {
    SetTargetFPS(30); // Change this value to increase/decrease animation time

    const int max_barHeight = GetScreenHeight() - 100;
    const int min_barHeight = 20;
    const int bar_count = GetScreenWidth() / (bar_width + 1);
    comparision_count = 0;
    std::vector<int> dataset;
    for (int i = 0; i < bar_count; i++) {
        dataset.push_back(GetRandomValue(min_barHeight, max_barHeight));
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
            quickSort(dataset, 0, dataset.size() - 1);
            isSorted = true;
        }
        DrawState(dataset, -1, -1);
    }
}
