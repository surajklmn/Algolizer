#include "queue.h"
#include "main.h"
#include <raylib.h>
#include <raygui/raygui.h>
#include <stack>
#include "utils/InputBox.h"
#include <string>
#include <chrono>
#include <thread>

extern std::stack<screen> screenStack;
extern screen currentscreen;

struct Element{ 
    Rectangle dimension;
    Color color;
    std::string text;
    Vector2 line;
  };



void RunQueueVisualizer(){
    const int box_width = 55;
    const int box_height = 55;
    const int starting_X = 30;
    const int element_gap = 70;
    bool dataEntered = false;
    const Color base_color = DARKGRAY;
    InputBox input_widget = InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    std::vector<Element> queue_item;
 
 
    while(!WindowShouldClose()){

     BeginDrawing();
     ClearBackground(RAYWHITE);
     DrawText("Press Enter To Enqueue Element",30,20,15,GRAY);
     DrawText("Press D To Dequeue Element",30,40,15,GRAY);
     DrawText("Press B To exit",30,60,15,GRAY);
    if(IsKeyPressed(KEY_B)){
        currentscreen = screenStack.top();
        break;
    } 
    if(IsKeyPressed(KEY_ENTER)){
       input_widget.Update();
       std::string data;
       if(!input_widget.IsEnteringInput()){
            data = std::to_string(input_widget.GetInputValue());
            dataEntered = true;    
         }
        if(dataEntered){
                if(queue_item.empty()){
                    Rectangle rectangle = {starting_X,300,box_width,box_height};
                     Color color = DARKGREEN;
                     queue_item.push_back({rectangle,color,data});
                }
                else{

                Rectangle lastElement = queue_item.back().dimension;
                Rectangle rectangle = {lastElement.x + element_gap , 300, box_width,box_height};
                Vector2 line_start = queue_item.back().line;
                line_start.x = lastElement.width+lastElement.x;
                line_start.y = lastElement.y+lastElement.height/2;
                queue_item.push_back({rectangle,base_color,data,line_start});
                 
            }
        dataEntered = false; 
        }
    }
    if(input_widget.IsEnteringInput()){
            input_widget.Draw();
    }
    if(IsKeyPressed(KEY_D)){
        if(!queue_item.empty()){
                              queue_item.erase(queue_item.begin());
                 queue_item.begin()->color = DARKGREEN;
        }  
    }

  
    for(int i=0;i<queue_item.size();i++){ 
         DrawRectangleRec(queue_item[i].dimension, queue_item[i].color);
         
       

    
        if(i>0){
            DrawLineEx(queue_item[i].line,{queue_item[i].dimension.x,queue_item[i].dimension.y+(box_height/2.0f)},2.0f, BLACK);
            DrawTriangle( {queue_item[i].dimension.x-5,queue_item[i].dimension.y+(box_height/2.0f)-5}, 
                        {queue_item[i].dimension.x-5,queue_item[i].dimension.y+(box_height/2.0f)+5},
                        
                         {queue_item[i].dimension.x+1,queue_item[i].dimension.y+(box_height/2.0f)}, BLACK);

            }
        
        if(i>0 && i== queue_item.size()-1){
                    DrawRectangleRec(queue_item[i].dimension, MAROON);

            }
         DrawText(queue_item[i].text.c_str(),queue_item[i].dimension.x+(box_width/2.0f)-18,
                 queue_item[i].dimension.y+(box_height/2.0f)-5,20,WHITE);
         

    }
   


    // Drawing Indicators

    if(!queue_item.empty()){
        
        const Rectangle dimensionS = queue_item.begin()->dimension;
        const Vector2 head_line = {dimensionS.x+(box_width/2.0f),dimensionS.y-30};
        DrawLineEx(head_line,{dimensionS.x+(box_width)/2.0f,dimensionS.y},2.0f,LIME);
        DrawTriangle(
                     {dimensionS.x+(box_width)/2.0f+10,dimensionS.y-10},
                     {dimensionS.x+(box_width)/2.0f-10,dimensionS.y-10},
                     {dimensionS.x+(box_width)/2.0f,dimensionS.y+1},
                     DARKGREEN);
        
        DrawText("Front",dimensionS.x+(box_width/2.0f)-20,dimensionS.y-45,15,BLACK);

        const Rectangle dimensionE = queue_item.back().dimension;
        const Vector2 tail_line = {dimensionE.x+(box_width/2.0f),(dimensionE.y+box_height)+30};
        DrawLineEx(tail_line,{dimensionE.x+(box_width/2.0f),dimensionE.y+box_height},2.0f,MAROON);
        DrawTriangle({dimensionE.x+(box_width/2.0f),dimensionE.y+box_height-1},
                     {dimensionE.x+(box_width/2.0f)-10,dimensionE.y+box_height+10},
                     {dimensionE.x+(box_width/2.0f)+10,dimensionE.y+box_height+10},
                     RED);

         DrawText("Rear",dimensionE.x+(box_width/2.0f)-15,dimensionS.y+box_height+30,15,BLACK);
            

 
    }  


    EndDrawing();
    }
    
    

}
