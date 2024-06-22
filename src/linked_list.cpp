#include "linked_list.hpp"
#include <raylib.h>
#include <raygui/raygui.h>
#include <stack>
#include <deque>
#include <string>
#include "main.h"
#include "utils/InputBox.h"
#include <deque>
#include <iostream>

struct Element {
    Rectangle dimension;
    Color color;
    std::string text;
    Vector2 line;
};

extern std::stack<screen> screenStack;
extern screen currentscreen;

void RunLinkedListVisualizer() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
    const int box_width = 55;
    const int box_height = 55;
    const int starting_X = 400;
    const int element_gap = 70;
    bool dataEntered = false;
    const Color base_color = DARKGRAY;
    InputBox input_widget = InputBox(Rectangle{800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40});
    std::deque<Element> queue_item;
    Rectangle spinner = {static_cast<float>(GetScreenWidth()-200), 100, 150, 30};
    int spinnerValue = 0;


    Rectangle button_insert_head = {20,20,150,30};
    Rectangle button_insert_tail = {20,60,150,30};
    Rectangle button_delete_head = {20,100,150,30};
    Rectangle button_delete_tail = {20,140,150,30};
    Rectangle button_insert_index = {static_cast<float>(GetScreenWidth()-200),20,150,30};
    Rectangle button_delete_index = {static_cast<float>(GetScreenWidth()-200),60,150,30};

    bool insertAtPosition = false;
    bool deleteAtPosition = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
  

        bool insertHead = GuiButton(button_insert_head,"Insert Head");
        bool insertTail = GuiButton(button_insert_tail,"Insert Tail");
        bool deleteHead = GuiButton(button_delete_head,"Delete Head");
        bool deleteTail = GuiButton(button_delete_tail,"Delete Tail");



        if (IsKeyPressed(KEY_B)) {
            currentscreen = screenStack.top();
            break;
        }

        if (insertTail) {
            std::string data = std::to_string(GetRandomValue(0,100));
                if (queue_item.empty()) {
                    Rectangle rectangle = {starting_X, 300, box_width, box_height};
                    Color color = DARKGREEN;
                    Vector2 line;
                    line.x = rectangle.x - (element_gap-box_width);
                    line.y = rectangle.y + rectangle.height/2;
                    queue_item.push_back({rectangle, color, data,line});
                } else {
                    Rectangle lastElement = queue_item.back().dimension;
                    Rectangle rectangle = {lastElement.x + element_gap, 300, box_width, box_height};
                    Vector2 line_start = queue_item.back().line;
                    line_start.x = lastElement.x + lastElement.width;
                    line_start.y = lastElement.y + lastElement.height / 2;
                    queue_item.push_back({rectangle, base_color, data, line_start});
                }
               
        }
        if (input_widget.IsEnteringInput()) {
            input_widget.Draw();
        }
        // Deletion Front 
        if (deleteHead) {
            if (!queue_item.empty()) {
                queue_item.pop_front();
                if (!queue_item.empty()) queue_item.begin()->color = DARKGREEN;
            }
        }

        if (insertHead) {
            int random_value = GetRandomValue(0, 100);
   
            Vector2 line;
            if (queue_item.empty()) {
                Rectangle rectangle = {starting_X, 300, box_width, box_height};
                line.x = rectangle.x - (element_gap-box_width);
                line.y = rectangle.y + rectangle.height/2;
                queue_item.push_front({rectangle, DARKGREEN, std::to_string(random_value),line});
            } else {
                auto firstElement = queue_item.begin(); 
                Rectangle rectangle = {firstElement->dimension.x - element_gap, 300, box_width, box_height};
                line.x = rectangle.x - (element_gap-box_width);
                line.y = rectangle.y + rectangle.height/2;
                queue_item.push_front({rectangle,DARKGREEN, std::to_string(random_value),line});
                firstElement->color = base_color;
                 
                                 
            }
        }

    // Deletion End
        if(deleteTail){
            if(!queue_item.empty()){
                queue_item.pop_back();
                if (!queue_item.empty()) queue_item.begin()->color = DARKGREEN;

            }
        }

    // Insertion At Index
        if(!queue_item.empty() && queue_item.size() > 1){
            GuiSpinner(spinner,"Select Position ",&spinnerValue,0,queue_item.size()-1,false);
            insertAtPosition = GuiButton(button_insert_index,"Insert At Position");
            deleteAtPosition = GuiButton(button_delete_index,"Delete At Position");
        } 

        if(insertAtPosition){
            int index = spinnerValue;
            auto iterator = queue_item.begin() + index;
          
            if(index == 0){
                Vector2 line;
                auto firstElement = queue_item.begin(); 
                Rectangle rectangle = {firstElement->dimension.x - element_gap, 300, box_width, box_height};
                line.x = rectangle.x - (element_gap-box_width);
                line.y = rectangle.y + rectangle.height/2;
                queue_item.push_front({rectangle,DARKGREEN, std::to_string(GetRandomValue(0, 100)),line});
                firstElement->color = base_color;

            }
            if(index == queue_item.size()-1){
                    Rectangle lastElement = queue_item.back().dimension;
                    Rectangle rectangle = {lastElement.x + element_gap, 300, box_width, box_height};
                    Vector2 line_start = queue_item.back().line;
                    line_start.x = lastElement.x + lastElement.width;
                    line_start.y = lastElement.y + lastElement.height / 2;
                    queue_item.push_back({rectangle, base_color,  std::to_string(GetRandomValue(0, 100)), line_start}); 
            }else{
                Color base_color = GRAY;
                Vector2 line;
                Rectangle element_dimension = queue_item[index].dimension;
                line.x = element_dimension.x-15;
                line.y = element_dimension.y+element_dimension.height/2;
                Element node = {element_dimension,base_color,std::to_string(GetRandomValue(20,30)),line};
                
                queue_item.insert(queue_item.begin()+index,node);
       
                for(int i=index+1;i<queue_item.size();i++){
                    queue_item[i].dimension.x +=element_gap;
                    queue_item[i].line.x += element_gap;
                }

                for(int i=0;i<queue_item.size();i++)
                {
                    std::cout << "Data = " << queue_item[i].text << std::endl;
                    std::cout << "Dimensions : X = " << queue_item[i].dimension.x << " Y= " << queue_item[i].dimension.y << std::endl;
                    std::cout << "-----" << std::endl;
                }
                 
                
            }

             
            insertAtPosition = false;
    
        }
        
        if(deleteAtPosition){
            int index = spinnerValue;
            auto iterator = queue_item.begin() + index;
            if(index == 0){
                queue_item.pop_front();
            }else if(index == queue_item.size()-1){
                queue_item.pop_back();
            }else{
                queue_item.erase(iterator);
                for(int i=1;i<queue_item.size();i++){
                    queue_item[i].dimension.x -=element_gap;
                    queue_item[i].line.x -=element_gap;
                }

            }



            deleteAtPosition = false;
        }



        for (int i = 0; i < queue_item.size(); i++) {
            DrawRectangleRec(queue_item[i].dimension, queue_item[i].color);

            if (i > 0) {
                DrawLineEx(queue_item[i].line, {queue_item[i].dimension.x, queue_item[i].dimension.y + (box_height / 2.0f)}, 2.0f, BLACK);
                DrawTriangle({queue_item[i].dimension.x - 5, queue_item[i].dimension.y + (box_height / 2.0f) - 5},
                             {queue_item[i].dimension.x - 5, queue_item[i].dimension.y + (box_height / 2.0f) + 5},
                             {queue_item[i].dimension.x + 1, queue_item[i].dimension.y + (box_height / 2.0f)}, BLACK);
            }

            if (i > 0 && i == queue_item.size() - 1) {
                DrawRectangleRec(queue_item[i].dimension, MAROON);
            }
            DrawText(queue_item[i].text.c_str(), queue_item[i].dimension.x + (box_width / 2.0f) - 18,
                     queue_item[i].dimension.y + (box_height / 2.0f) - 5, 20,WHITE);
        }

        // Drawing Indicators
        if (!queue_item.empty()) {
            const Rectangle dimensionS = queue_item.begin()->dimension;
            const Vector2 head_line = {dimensionS.x + (box_width / 2.0f), dimensionS.y - 30};
            DrawLineEx(head_line, {dimensionS.x + (box_width) / 2.0f, dimensionS.y}, 2.0f, LIME);
            DrawTriangle(
                {dimensionS.x + (box_width) / 2.0f + 10, dimensionS.y - 10},
                {dimensionS.x + (box_width) / 2.0f - 10, dimensionS.y - 10},
                {dimensionS.x + (box_width) / 2.0f, dimensionS.y + 1},
                DARKGREEN);
            DrawText("Head", dimensionS.x + (box_width / 2.0f) - 20, dimensionS.y - 45, 15, BLACK);

            const Rectangle dimensionE = queue_item.back().dimension;
            const Vector2 tail_line = {dimensionE.x + (box_width / 2.0f), (dimensionE.y + box_height) + 30};
            DrawLineEx(tail_line, {dimensionE.x + (box_width / 2.0f), dimensionE.y + box_height}, 2.0f, MAROON);
            DrawTriangle({dimensionE.x + (box_width / 2.0f), dimensionE.y + box_height - 1},
                         {dimensionE.x + (box_width / 2.0f) - 10, dimensionE.y + box_height + 10},
                         {dimensionE.x + (box_width / 2.0f) + 10, dimensionE.y + box_height + 10},
                         RED);
            DrawText("Tail", dimensionE.x + (box_width / 2.0f) - 15, dimensionS.y + box_height + 30, 15, BLACK);
        }

        EndDrawing();
    }
}

