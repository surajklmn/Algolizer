#include "linked_list.hpp"
#include <raylib.h>
#include <raygui/raygui.h>
#include <stack>
#include <deque>
#include <string>
#include "main.h"
#include "utils/InputBox.h"

#include <iostream>
enum InputHolder{
    INSERT_HEAD,
    DELETE_HEAD,
    INSERT_INDEX,
    INSERT_TAIL,
    NONE,
};



extern std::stack<screen> screenStack;
extern screen currentscreen;

void RunLinkedListVisualizer(){

    const int box_width = 55;
    const int box_height = 55;
    const int starting_X = 400;
    const int element_gap = 70;
    bool dataEntered = false;
    int startingPosX = 300;
    const Color base_color = DARKGRAY;
    InputBox input_widget = InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    std::deque<int> list;
    list.push_front(20);
    list.push_front(30);
    list.push_back(450);
    InputHolder current_holder = NONE; 
    Rectangle button_InsertF = {20,20,150,30};
    Rectangle button_InsertL = {20,60,150,30};
    Rectangle button_DeleteF = {20,100,150,30};
    Rectangle button_DeleteL = {20,140,150,30};

  
    while(!WindowShouldClose()){
    GuiSetStyle(DEFAULT,TEXT_SIZE,12);

   
     BeginDrawing();
     ClearBackground(RAYWHITE);
 
   //  DrawText("Press B To exit",130,60,15,GRAY);
    if(IsKeyPressed(KEY_B)){
        currentscreen = screenStack.top();
        break;
    }
    if(IsKeyPressed(KEY_A)){
        list.push_front(GetRandomValue(10, 20));
        startingPosX -= element_gap;
    }
    if(IsKeyPressed(KEY_I)){
        list.push_back(GetRandomValue(10, 20));
    
    }
    if(IsKeyPressed(KEY_M)){
        int random_Value = GetRandomValue(50, 60);
        int index;
        std::cout << "Index :";
        std::cin >> index;
        list.insert(list.begin()+index,random_Value);
    }
    


    // Button Rendering
        bool insert_f = GuiButton(button_InsertF,"Insert At Head");
        bool insert_l = GuiButton(button_InsertL,"Insert At Tail");
        bool delete_f = GuiButton(button_DeleteF,"Delete Head");
        bool delete_l = GuiButton(button_DeleteL,"Delete Tail");
    //--

        
    int rectangle_position = startingPosX; 
    for(int i=0;i<list.size();i++){
      
        DrawRectangle(rectangle_position, 300,50,50,GRAY);
        DrawText(TextFormat("%i",list[i]),rectangle_position+(50/3),300+(50/2),15,BLACK);
            rectangle_position +=element_gap;
    
    }
    
   
    EndDrawing();
    }

}

