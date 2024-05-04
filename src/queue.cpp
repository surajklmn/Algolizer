#include "queue.h"
#include "main.h"
#include <raylib.h>
#include <raygui/raygui.h>
#include <stack>
#include "utils/InputBox.h"
#include <string>

extern std::stack<screen> screenStack;
extern screen currentscreen;

struct Element{ 
    Rectangle dimension;
    Color color;
    Vector2 line;
};



void RunQueueVisualizer(){
    const int box_width = 50;
    const int box_height = 50;
    const int starting_X = 30;
    const int element_gap = 70;
    const Color base_color = GRAY;
    int queue_size;
    InputBox input_widget = InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    std::vector<Element> queue_item;

    std::vector<Rectangle> Rectangles; 
    while(!WindowShouldClose()){

     BeginDrawing();
     ClearBackground(RAYWHITE); 
     DrawText("Press E To Enqueue Element",30,40,15,GRAY);
     DrawText("Press D To Dequeue Element",30,60,15,GRAY);
     
    if(IsKeyPressed(KEY_E)){
        if(queue_item.empty()){
            Rectangle rectangle = {starting_X,300,box_width,box_height};
            Color color = GREEN;
            queue_item.push_back({rectangle,color});
        }else{
                Rectangle lastElement = queue_item.back().dimension;
                Rectangle rectangle = {lastElement.x + element_gap , 300, box_width,box_height};
                Vector2 line_start = queue_item.back().line;
                line_start.x = lastElement.width+lastElement.x;
                line_start.y = lastElement.y+lastElement.height/2;
                queue_item.push_back({rectangle,base_color,line_start});
            }
    }
    if(IsKeyPressed(KEY_D)){
        if(!queue_item.empty()){
                 queue_item.erase(queue_item.begin());
                 queue_item.begin()->color = GREEN;
        }  
    }


    for(Element element : queue_item){

        DrawRectangleRec(element.dimension, element.color);
    }

    for(int i=0;i<queue_item.size();i++){
        DrawRectangleRec(queue_item[i].dimension, queue_item[i].color);
        if(i>0){
            DrawLineEx(queue_item[i].line,{queue_item[i].dimension.x,queue_item[i].dimension.y+(box_height/2.0f)},2.0f, BLACK);
            DrawTriangle( {queue_item[i].dimension.x-5,queue_item[i].dimension.y+(box_height/2.0f)-5}, 
                        {queue_item[i].dimension.x-5,queue_item[i].dimension.y+(box_height/2.0f)+5},
                        
                         {queue_item[i].dimension.x+1,queue_item[i].dimension.y+(box_height/2.0f)}, BLACK);

            }
         

    }



    EndDrawing();
    }
    
    

}
