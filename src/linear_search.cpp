#include "linear_search.h"
#include <iostream>
#include <random>
#include <raylib.h>
#include <chrono>
#include <thread>
void runLinearSearchVisualizer(){
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 550;
const int ARRAY_SIZE = 20;
const int ELEMENT_WIDTH = 30;
const int ELEMENT_HEIGHT = 50;
const int SEARCH_DELAY = 500;


    // Generate a random array of integers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    int arr[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = dis(gen);
    }

    // Linear search variables
    int targetValue = 0;
    int currentIndex = 0;
    bool found = false;
    bool isTargetSet = false;
    // Main game loop
    while (!IsKeyPressed(KEY_BACKSPACE)) {
        // Clear the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the array elements
        for (int i = 0; i < ARRAY_SIZE; i++) {
            int x = i * ELEMENT_WIDTH + 50;
            int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
            DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, SKYBLUE);
            DrawText(std::to_string(arr[i]).c_str(), x + 5, y + 5, 20, BLACK);
        }

        // Get user input for target value
        if (IsKeyPressed(KEY_R)) {
            isTargetSet = false;
            // Randomize the array
            for (int i = 0; i < ARRAY_SIZE; i++) {
                arr[i] = dis(gen);
            }
            found = false;
            currentIndex = 0;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            // Get user input for target value
            std::cout << "Enter the target value: ";
            std::cin >> targetValue;
            isTargetSet = true;
            found = false;
            currentIndex = 0;
        }

        // Visualize the linear search
       if(isTargetSet){
        if (!found) {
            int x = currentIndex * ELEMENT_WIDTH + 50;
            int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
            DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, RED);
            DrawText(std::to_string(arr[currentIndex]).c_str(), x + 5, y + 5, 20, BLACK);

            // Add a delay to the search
            std::this_thread::sleep_for(std::chrono::milliseconds(SEARCH_DELAY));

            if (arr[currentIndex] == targetValue) {
                found = true;
            }else if(currentIndex  == ARRAY_SIZE-1){
                DrawText("Target value found at index -1",
                    WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2, 30, GREEN);
            } 
            else {
                currentIndex++;
            }
        } else {
            int x = currentIndex * ELEMENT_WIDTH + 50;
            int y = WINDOW_HEIGHT - ELEMENT_HEIGHT - 50;
            DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, GREEN);
            DrawText(std::to_string(arr[currentIndex]).c_str(), x + 5, y + 5, 20, BLACK);
            DrawText(("Target value found at index " + std::to_string(currentIndex)).c_str(),
                    WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2, 30, GREEN);
        }
       
        }

        // Display instructions
        DrawText("Press 'R' to randomize the array", 10, 10, 20, GRAY);
        DrawText("Press 'Enter' to enter a target value", 10, 40, 20, GRAY);
        DrawText("Press 'Backspace' to exit", 10, 70, 20, GRAY);
        EndDrawing();
    }


}

