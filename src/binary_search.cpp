#include "binary_search.h"
#include "main.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <raylib.h>
#include <chrono>
#include <stack>
#include <thread>
#include <raygui/raygui.h>
#include "utils/InputBox.h"

extern std::stack<screen> screenStack;
extern screen currentscreen;

void runBinarySearchVisualizer() {
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 550;
    const int ARRAY_SIZE = 20;
    const int ELEMENT_WIDTH = 40;
    const int ELEMENT_HEIGHT = 50;
    const int SEARCH_DELAY = 500;

    // Generate a random sorted array of integers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    int arr[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = dis(gen);
    }
    std::sort(arr, arr + ARRAY_SIZE); // Sort the array

    char inputText[64] = "";
    // Binary search variables
    int targetValue = 0;
    int left = 0;
    int right = ARRAY_SIZE - 1;
    int mid;
    bool found = false;
    bool isTargetSet = false;
    bool isEnteringInput = false;

    // Main game loop
    InputBox inputbox(Rectangle{800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40});

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the array elements
        for (int i = 0; i < ARRAY_SIZE; i++) {
            int x = i * ELEMENT_WIDTH + 50;
            int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
            DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, SKYBLUE);
            DrawText(std::to_string(arr[i]).c_str(), x + 5, y + 5, 20, BLACK);
        }

        if (IsKeyPressed(KEY_B)) {
            currentscreen = screenStack.top();
            break;
        }

        // Get user input for target value
        if (IsKeyPressed(KEY_R)) {
            isTargetSet = false;
            // Randomize and sort the array
            for (int i = 0; i < ARRAY_SIZE; i++) {
                arr[i] = dis(gen);
            }
            std::sort(arr, arr + ARRAY_SIZE);
            found = false;
            left = 0;
            right = ARRAY_SIZE - 1;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            inputbox.Update();
            if (!inputbox.IsEnteringInput()) {
                isTargetSet = true;
                targetValue = inputbox.GetInputValue();
                found = false;
                left = 0;
                right = ARRAY_SIZE - 1;
            }
        }

        if (inputbox.IsEnteringInput()) {
            inputbox.Draw();
        }

        // Visualize the binary search
        if (isTargetSet) {
            DrawText(("Target Value : " + std::to_string(targetValue)).c_str(), 600, 40, 20, GRAY);
            if (!found) {
                if (left <= right) { // Check if the search range is valid
                    mid = left + (right - left) / 2;
                    int x = mid * ELEMENT_WIDTH + 50;
                    int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
                    DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, RED);
                    DrawText(std::to_string(arr[mid]).c_str(), x + 5, y + 5, 20, BLACK);

                    // Highlight the search range
                    for (int i = left; i <= right; i++) {
                        int x = i * ELEMENT_WIDTH + 50;
                        int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
                        DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, YELLOW);
                        DrawText(std::to_string(arr[i]).c_str(), x + 5, y + 5, 20, BLACK);
                    }

                    // Add a delay to the search
                    std::this_thread::sleep_for(std::chrono::milliseconds(SEARCH_DELAY));

                    if (arr[mid] == targetValue) {
                        found = true;
                    } else if (arr[mid] < targetValue) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                } else { // Element not found
                    DrawText("Target value not found", WINDOW_WIDTH / 2 - 350, WINDOW_HEIGHT / 2, 30, RED);
                    found = false; 
                }
            } else {
                int x = mid * ELEMENT_WIDTH + 50;
                int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
                DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, GREEN);
                DrawText(std::to_string(arr[mid]).c_str(), x + 5, y + 5, 20, BLACK);
                DrawText(("Target value found at index " + std::to_string(mid)).c_str(),
                         WINDOW_WIDTH / 2 - 350, WINDOW_HEIGHT / 2, 30, GREEN);
            }
        }

        // Display instructions
        DrawText("Press 'R' to randomize and sort the array", 10, 10, 20, GRAY);
        DrawText(("Sample Size : " + std::to_string(ARRAY_SIZE)).c_str(), 600, 10, 20, GRAY);
        DrawText("Press 'Enter' to enter a target value", 10, 40, 20, GRAY);

        EndDrawing();
    }
}
