#include "stack.h"
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



void RunStackVisualizer(){
    const int box_width = 55;
    const int box_height = 55;
    const int starting_X = 700;
    const int element_gap = 20;
    bool dataEntered = false;
    const Color base_color = DARKGRAY;
    InputBox input_widget = InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    std::vector<Element> stack_item;
 
 
    while(!WindowShouldClose()){

     BeginDrawing();
     ClearBackground(RAYWHITE);
     DrawText("Press Enter To PUSH Element",30,20,15,GRAY);
     DrawText("Press D To POP Element",30,40,15,GRAY);
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
    if(stack_item.empty()){
        // If stack is empty, simply add the new element at the starting position
        Rectangle rectangle = {starting_X, 300, box_width, box_height};
        stack_item.push_back({rectangle, base_color, data});
    }
    else {
        // If stack is not empty, calculate position based on the last element
        Rectangle lastElement = stack_item.back().dimension;
         Vector2 line_start = stack_item.back().line;
        line_start.x = lastElement.x;
        line_start.y = lastElement.y+lastElement.height/2;
        Rectangle rectangle = {lastElement.x - box_width - element_gap, lastElement.y, box_width, box_height}; // Position to the left of the last element
         // You can change the color if needed
        stack_item.push_back({rectangle, base_color, data,line_start});
    }
    dataEntered = false; // Reset dataEntered flag after pushing data
}


    }
    if(input_widget.IsEnteringInput()){
            input_widget.Draw();
    }
   if(IsKeyPressed(KEY_D)){
    if(!stack_item.empty()){
        stack_item.pop_back(); // Remove the last element (leftmost item)
  
    }  
}


  
    for(int i=0;i<stack_item.size();i++){ 
         DrawRectangleRec(stack_item[i].dimension, stack_item[i].color);
         
       

    
        if(i>0){
            DrawLineEx(stack_item[i].line,{stack_item[i].dimension.x+box_width,stack_item[i].dimension.y+(box_height/2.0f)},2.0f, BLACK);
            DrawTriangle( {stack_item[i].dimension.x+box_width-1,stack_item[i].dimension.y+(box_height/2.0f)}, 
                          {stack_item[i].dimension.x+box_width+5,stack_item[i].dimension.y+(box_height/2.0f)+5},
                          {stack_item[i].dimension.x+box_width+5,stack_item[i].dimension.y+(box_height/2.0f)-5},

                           
                        
                         BLACK
                         );
            }
        
        if((i>0 && i== stack_item.size()-1) || (stack_item.size()==1)){
                    DrawRectangleRec(stack_item[i].dimension, MAROON);

            }
         DrawText(stack_item[i].text.c_str(),stack_item[i].dimension.x+(box_width/2.0f)-18,
                 stack_item[i].dimension.y+(box_height/2.0f)-5,20,WHITE);
         

    }
   


    // Drawing Indicators

    if(!stack_item.empty()){
        
        const Rectangle dimensionS = stack_item.begin()->dimension;
        const Vector2 head_line = {dimensionS.x+(box_width/2.0f),dimensionS.y-30};
      
        


        const Rectangle dimensionE = stack_item.back().dimension;
        const Vector2 tail_line = {dimensionE.x+(box_width/2.0f),(dimensionE.y+box_height)+30};
        DrawLineEx(tail_line,{dimensionE.x+(box_width/2.0f),dimensionE.y+box_height},2.0f,MAROON);
        DrawTriangle({dimensionE.x+(box_width/2.0f),dimensionE.y+box_height-1},
                     {dimensionE.x+(box_width/2.0f)-10,dimensionE.y+box_height+10},
                     {dimensionE.x+(box_width/2.0f)+10,dimensionE.y+box_height+10},
                     RED);

         DrawText("TOP",dimensionE.x+(box_width/2.0f)-15,dimensionS.y+box_height+30,15,BLACK);
            

 
    }  


    EndDrawing();
    
    }
    
    

}
