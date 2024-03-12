#include <raylib.h>
#include <iostream>
#include <random>
#include <ranges>
#include <thread>
#include <chrono>

void DrawState(std::vector<int>& vector,const int blue , const int red){
    BeginDrawing();
    ClearBackground(RAYWHITE);
 
    Color draw_color;

       
       int rectWidth = 10; // Adjust this value as needed
       int index = 0;
     
  
    for (int counter = 0;counter < vector.size();counter++) {
           if(counter == blue){
               draw_color = BLUE;
           }else if(counter == red){
               draw_color = RED;
           }else {
               draw_color = BLACK;
           }
    
           DrawRectangle(index, 599-vector[counter], rectWidth, vector[counter], draw_color);
           index += rectWidth + 2;
       }
    EndDrawing();
        

}

int main(){
    InitWindow(800, 600, "title");
   
    SetTargetFPS(60);
    
    std::random_device rd;
    std::uniform_int_distribution d(1,600);
    std::vector<int> dataset;

  
    for(int i =0;i<10;i++){
        dataset.push_back(d(rd));
    }
    
    bool sorted = false;
  

    while (!WindowShouldClose()) {
   
      
        
        if(!sorted){
                for (int i = 0; i < dataset.size(); i++) {
                    for (int j = i; j < dataset.size(); j++) {
                        if (dataset[j] < dataset[i]) {
                            std::swap(dataset[j], dataset[i]);
                            
                            
                        }
                        
                        DrawState(dataset, j, i);
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                }
            sorted = true;
         
        }
          // Sorting complete

        EndDrawing();
    }
    
    
    CloseWindow();
    return 0;
}

