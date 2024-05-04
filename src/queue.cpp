#include "queue.h"
#include "main.h"
#include <raylib.h>
#include <raygui/raygui.h>
#include <stack>
#include "utils/InputBox.h"

extern std::stack<screen> screenStack;
extern screen currentscreen;



void RunQueueVisualizer(){
    const int box_width = 50;
    const int box_height = 50;
    const int starting_X = 30;
    const int element_gap = 70;
    int queue_size;
    InputBox input_widget = InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    std::vector<Rectangle> Rectangles; 
    while(!WindowShouldClose()){

     BeginDrawing();
     ClearBackground(RAYWHITE); 
     DrawText("Press E To Enqueue Element",30,40,15,GRAY);
     DrawText("Press D To Dequeue Element",30,60,15,GRAY);
    
     if(IsKeyPressed(KEY_ENTER)){
        input_widget.Update();
        if(!input_widget.IsEnteringInput()){
            queue_size = input_widget.GetInputValue();
        }
    } 
    if(input_widget.IsEnteringInput()){
        input_widget.Draw();
    }


    if(IsKeyPressed(KEY_E)){
        if(Rectangles.empty()){
            Rectangle rectangle = {starting_X,300,box_width,box_height};
            Rectangles.push_back(rectangle);
        }else{
                Rectangle rectangle = {Rectangles.back().x + element_gap , 300, box_width,box_height};
               
                Rectangles.push_back(rectangle);
            }
    }
    if(IsKeyPressed(KEY_D)){
        if(!Rectangles.empty()){
                 Rectangles.erase(Rectangles.begin());
             
            }  
    }


    for(Rectangle rectangle_data : Rectangles){

        DrawRectangleRec(rectangle_data, GRAY);
    }
   




    EndDrawing();
    }
    
    

}
