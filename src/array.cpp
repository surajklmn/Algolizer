#include <raylib.h>
#include <iostream>
#include <stack>
#include "main.h"

extern std::stack<screen> screenStack;
extern screen currentscreen;

#define SIZE 10
int array[SIZE] = {0};
int numElements = 0;


void deleteElementAtIndex(int index){
    if(index >=0 && index<SIZE){
        for(int i=index;i<SIZE-1;i++){
            array[i] = array[i+1];
        }
        array[SIZE-1]=0;
    }
    numElements--;
}


void insertAtBeginning(int element){
    if(numElements < SIZE){
        for(int i=numElements;i>0;i--){
            array[i] = array[i-1];
        }
        array[0] = element;
        numElements++;
    }
}

void insertAtEnd(){
    for(int i=0;i<SIZE;i++){
        if(array[i] == 0){
            array[i] = GetRandomValue(1, 100);
            numElements++;
            break;
        }
    }
}

void insertElementAtIndex(int index){
    int value = GetRandomValue(0, 100);
    if (index >= 0 && index < SIZE && numElements < SIZE) {
        for (int i = numElements; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        numElements++;
    }
}


void deleteAtEnd(){
    for(int i=SIZE-1;i>=0;i--){
        if(array[i]!=0){
            array[i] = 0;
            numElements--;
            break;
        }
    }
}

void deleteFromFront() {
    if (numElements > 0) {
        for (int i = 0; i < SIZE - 1; i++) {
            array[i] = array[i + 1];      
        }
        array[SIZE - 1] = 0; 

        numElements--;    
    }
}


void runArrayVisualizer(){

       
    while(!WindowShouldClose()){

    
           // Draw Text
        // -- B for Back
        // -- I insert at End
        // -- O Insert at Front
        // -- P Insert at Index

        // -- D Delete From Back
        // -- A Delete At Index
        // -- S Delete From Front
        if(IsKeyPressed(KEY_I)){
            insertAtEnd();
        }else if(IsKeyPressed(KEY_O)){
            int element = GetRandomValue(0, 100);
            insertAtBeginning(element);
        }else if(IsKeyPressed(KEY_P)){
            int index;
            std::cout << "Enter Index :" << std::endl;
            std::cin >> index;
            insertElementAtIndex(index);
        }else if(IsKeyPressed(KEY_D)){
            deleteAtEnd();
        }else if(IsKeyPressed(KEY_A)){
            int index;
            std::cout << "Enter Index :" << std::endl;
            std::cin >> index;
            deleteElementAtIndex(index);
        }else if(IsKeyPressed(KEY_S)){
            deleteFromFront();
        }
        else if(IsKeyPressed(KEY_B)){
            currentscreen = screenStack.top();
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
     
              DrawText("Press 'B' To move back to previous screen", 10, 10, 15, BLACK);
              DrawText("Press 'I' To Insert At End", 10, 30, 15, BLACK);
              DrawText("Press 'O' To Insert At Front", 10, 50, 15, BLACK);
              DrawText("Press 'P' To Insert At Index", 10, 70, 15, BLACK);

              DrawText("Press 'D' To Delete From Back", 10, 90, 15, BLACK);
              DrawText("Press 'A' To Delete At Index", 10, 110, 15, BLACK);
              DrawText("Press 'S' To Delete From Front", 10, 130, 15, BLACK);
                
              DrawText("Data -> ",20,260,20,BLACK);
              DrawText("Index -> ",20,220,20,BLACK);
        for(int i=0;i<SIZE;i++){
            DrawRectangle(140 + i * 50, 250, 40, 40, BLUE); 
            DrawText(TextFormat("%d", array[i]), 150 + i * 50, 260, 20, BLACK);  
            DrawText(TextFormat("%d", i), 155 + i * 50, 220, 20, BLACK); 
        }
        
       EndDrawing(); 

    }





}
