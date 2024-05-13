#include "raylib.h"
#include <chrono>
#include <thread>

const int screenWidth = 800;
const int screenHeight = 600;
const int barWidth = 10;
const int numBars = screenWidth / barWidth;

// Function to swap two elements in an array
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Bubble sort algorithm with visualization
void bubbleSortVisual(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Visualize comparison
            BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int k = 0; k < numBars; k++) {
                if (k == j || k == j + 1) DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], RED);
                else DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], BLUE);
            }
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            if (arr[j] > arr[j + 1]) {
                // Swap and visualize
                swap(arr[j], arr[j + 1]);
                BeginDrawing();
                ClearBackground(RAYWHITE);
                for (int k = 0; k < numBars; k++) {
                    if (k == j || k == j + 1) DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], GREEN);
                    else DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], BLUE);
                }
                EndDrawing();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }
}

int main() {
    // Initialization
    InitWindow(screenWidth, screenHeight, "Bubble Sort Visualization");
    SetTargetFPS(60);

    int data[numBars];
    for (int i = 0; i < numBars; i++) {
        data[i] = GetRandomValue(10, screenHeight - 20);
    }

    while (!WindowShouldClose()) {
        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            bubbleSortVisual(data, numBars);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw bars
        for (int i = 0; i < numBars; i++) {
            DrawRectangle(i * barWidth, screenHeight - data[i], barWidth, data[i], BLUE);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

