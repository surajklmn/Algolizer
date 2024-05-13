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

// Selection sort algorithm with visualization
void selectionSortVisual(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            // Visualize comparison
            BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int k = 0; k < numBars; k++) {
                if (k == i || k == j) DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], RED);
                else DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], BLACK);
            }
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Swap and visualize
        swap(arr[minIdx], arr[i]);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int k = 0; k < numBars; k++) {
            if (k == i || k == minIdx) DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], GREEN);
            else DrawRectangle(k * barWidth, screenHeight - arr[k], barWidth, arr[k], BLACK);
        }
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
int main() {
    // Initialization
    InitWindow(screenWidth, screenHeight, "Selection Sort Visualization");
    SetTargetFPS(60);

    int data[numBars];
    for (int i = 0; i < numBars; i++) {
        data[i] = GetRandomValue(10, screenHeight - 20);
    }

    while (!WindowShouldClose()) {
        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            selectionSortVisual(data, numBars);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw bars
        for (int i = 0; i < numBars; i++) {
            DrawRectangle(i * barWidth, screenHeight - data[i], barWidth, data[i], BLACK);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
