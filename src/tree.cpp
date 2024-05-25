#include "tree.hpp"
#include "main.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <raylib.h>
#include <raygui/raygui.h>
#include <thread>
#include <stack>
#include "utils/InputBox.h"

extern std::stack<screen> screenStack;
extern screen currentscreen;


std::vector<int> TraversalOrder;
void Tree::InsertNode(int data){
    Node* data_node = new Node(data);
    if(root_node == nullptr){
        root_node = data_node;
        return;
    }

    if(nodeposition.find(data) !=nodeposition.end()){
        nodeposition[data]->node_frequency +=1;
        return;
    }

    Node* current_node = root_node;
    while(true){
        if(data < current_node->data){
            if(current_node->left_node == nullptr){
                current_node->left_node = data_node; 
                break;
            }
            current_node = current_node->left_node;
        }else{
            if(current_node->right_node ==nullptr){
                current_node->right_node = data_node;
                break;
            } 
            current_node = current_node->right_node;
        }
    }
}


void Tree::Deletion(Node* node,int data){
    if(node == nullptr) return;
    else if(data < node->data){
        Deletion(node->left_node,data);
    }else if(data > node->data){
        Deletion(node->right_node,data);
    }else if(node->data == data){
        Node* parent_node = GetParentNode(this->root_node,node);
        if(node->left_node == nullptr && node->right_node==nullptr){
            delete node;
            node = parent_node->left_node = parent_node->right_node = nullptr;
           
        }
        nodeposition.erase(data);
    }
}
void Tree::DeleteNode(int data){
    this->Deletion(this->root_node,data);
}

void Tree::TraversePre(Node* node){
    if(node == nullptr) return;
    TraversalOrder.push_back(node->data); 
    TraversePre(node->left_node); // Left
    TraversePre(node->right_node);

}
void Tree::TraverseIn(Node* node){
   if(node == nullptr) return;
   TraverseIn(node->left_node);
   TraversalOrder.push_back(node->data); 
   TraverseIn(node->right_node);
}

void Tree::TraversePos(Node* node){
    if(node == nullptr) return;
    TraversePos(node->left_node);
    TraversePos(node->right_node);
    TraversalOrder.push_back(node->data); 
}
int Tree::CalculateTreeHeight(Node* node){
    if(node == nullptr){
        return -1; 
    } 
    if(node->left_node == nullptr && node->right_node == nullptr){
        return 0;
    }
    int leftSubTreeH = CalculateTreeHeight(node->left_node);
    int rightSubTreeH = CalculateTreeHeight(node->right_node);

    return 1+std::max(leftSubTreeH,rightSubTreeH);
  
}
Node* Tree::GetParentNode(Node* node,Node* target_node){
    if(node == nullptr) return nullptr;
    if(node->left_node == target_node || node->right_node == target_node){
        return node;
    }else if(target_node->data < node->data){
        return GetParentNode(node->left_node, target_node);
    }else if(target_node->data > node->data){
        return GetParentNode(node->right_node,target_node);
    }
    return nullptr; // Return Null
};

void Tree::GetNodeAtDistance(Node* node,int distance,std::vector<int>& data){
    if(node == nullptr){
        return;
    }
    if(distance == 0){
        // GetValueAt
        data.push_back(node->data);
    }
    GetNodeAtDistance(node->left_node,distance-1,data);
    GetNodeAtDistance(node->right_node, distance-1,data);
}

void Tree::TraverseLevel(Node* node){
    for(int i=0;i<=this->getHeight();i++){
        std::vector<int> nodelist = this->NodeAtDistance(i);
        for(int node_value: nodelist){
           TraversalOrder.push_back(node_value); 
        }
    }


}


void Tree::SearchTraversal(Node* node, int data){

    if(node == nullptr){
        return;
    }
    TraversalOrder.push_back(node->data);
    if(node->data == data)
    {
        node->color = GREEN;
        return;
    }else if(data<node->data){
        SearchTraversal(node->left_node,data);
    }else if(data>node->data){
        SearchTraversal(node->right_node,data);
    }

}


void Tree::DrawTree(Node* node,int startingX,int startingY,int spacing){
    int Radius = 30;
    int level_height = Radius+60;

      
    DrawText("Press 'Enter' To Insert Value",GetScreenWidth()-400,20,12,BLACK);  
    Vector2 linestart_Left = {static_cast<float>(startingX-Radius),static_cast<float>(startingY)};
    Vector2 lineend_Left = {static_cast<float>(startingX-spacing-Radius),static_cast<float>(startingY+level_height)};
    
    Vector2 linestart_Right = {static_cast<float>(startingX+Radius),static_cast<float>(startingY)};
    Vector2 lineend_Right = {static_cast<float>(startingX+spacing+Radius),static_cast<float>(startingY+level_height)};
    Color linecolor = DARKGRAY;
    
    if(node == nullptr) return;

    // Drawing Instructions



    nodeposition.insert({node->data,node});
    if(node->node_frequency !=1){
             DrawText(TextFormat("%d",node->node_frequency),startingX-5,startingY-50,20,RED); 
    }
    DrawCircle(startingX,startingY,Radius,node->color);
    DrawText(TextFormat("%d",node->data),startingX-10,startingY-10,20,WHITE);
    
    if(node->left_node !=nullptr){
                  DrawLineEx(linestart_Left,lineend_Left,2,linecolor); 
        DrawTree(node->left_node,startingX-spacing,startingY+level_height,spacing/(1.5));
    }
    if(node->right_node !=nullptr){
           DrawLineEx(linestart_Right,lineend_Right,2,linecolor);  
        DrawTree(node->right_node,startingX+spacing,startingY+level_height,spacing/(1.5));
    }
 
}
//--------------------------------------------------------------------------


// Accessor Functions
void Tree::TraversePreOrder(){
    this->TraversePre(this->root_node);
}

void Tree::TraverseInOrder(){
    this->TraverseIn(this->root_node);
}
void Tree::TraversePostOrder(){
    this->TraversePos(this->root_node);
}
void Tree::LevelOrderTraverse(){
    this->TraverseLevel(this->root_node);
}

std::vector<int> Tree::NodeAtDistance(int distance){
    std::vector<int> data;
    GetNodeAtDistance(this->root_node, distance,data);
    return data;
   
}
const int Tree::getHeight(){
    return this->CalculateTreeHeight(this->root_node);
}

void Tree::DrawTreeStructure(){
    int startingX = GetScreenWidth()/2;
    int startingY = 140;
    DrawTree(this->root_node,startingX , 200 , 200);
}





void Tree::HighlightTraversal(){
  
    for(int item : TraversalOrder){
   
       
        nodeposition[item]->color = BLUE;
        BeginDrawing(); 
        ClearBackground(RAYWHITE); 
        DrawTreeStructure();
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        nodeposition[item]->color = DARKGRAY;
      
    }
}

void Tree::Search(int data){
    this->SearchTraversal(this->root_node,data);
}


// Visualizer Function
void RunTreeVisualizer(){
    
    Tree mytree;
    mytree.InsertNode(20);
    mytree.InsertNode(30);
    mytree.InsertNode(5);
    mytree.InsertNode(55);
    mytree.InsertNode(10);

    InputBox inputbox= InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    InputBox inputboxS= InputBox(Rectangle { 800 / 2.0 - 100, 600.0 / 2 - 100, 200, 40 });
    

    //--------- Gui Constants
    const int screenwidth = 1024;
    const int screenheight = 768;
  
    int data;
    //--------- Flags
    bool highlightTraverse = false;
    MaximizeWindow();
    SetTargetFPS(60); 
    //---------------Traversal Buttons Dimensions
    bool highlightmessage = false;
    Rectangle buttonPre = {20,20,150,30};
    Rectangle buttonIn = {20,60,150,30};
    Rectangle buttonPos = {20,100,150,30};
    Rectangle buttonLev = {20,140,150,30};
    Rectangle buttonSearch = {20,180,150,30};
    bool searchFlag = false;
    // ---------------------- Set Gui Configurations
    GuiSetStyle(DEFAULT,TEXT_SIZE,12);

    while(!WindowShouldClose()){
     BeginDrawing(); 
     ClearBackground(RAYWHITE);
        // ----------- Gui Text Components
        int y_coordinateText  = 20; 
        int x_coordinateText  = screenwidth-(screenwidth/4);  
        // ----------- Render Buttons
        bool preorder = GuiButton(buttonPre,"Preorder-Traversal");
        bool inorder = GuiButton(buttonIn,"Inorder-Traversal");
        bool postorder =GuiButton(buttonPos,"Postorder-Traversal");
        bool levelorder = GuiButton(buttonLev,"Levelorder-Traversal");
        bool search = GuiButton(buttonSearch,"Search");
        mytree.DrawTreeStructure();
        if(IsKeyPressed(KEY_D)){
            mytree.DeleteNode(10);
          
        }  
    
        if (IsKeyPressed(KEY_ENTER) && !searchFlag){
               
                 inputbox.Update();
                 if(!inputbox.IsEnteringInput()){
                 data = (inputbox.GetInputValue());
                 mytree.InsertNode(data);
             }

      }
      if(search || (searchFlag && inputboxS.IsEnteringInput() && IsKeyPressed(KEY_ENTER)) ){
          
            inputboxS.Update(); 

            TraversalOrder.clear();
            searchFlag = true;
            
            if(!inputboxS.IsEnteringInput()){
                 data = (inputboxS.GetInputValue()); 
                 searchFlag = false;
                mytree.Search(data);
                 highlightTraverse = true;
            
            }
          
               

 

        }

     if(inputbox.IsEnteringInput()){
              
            inputbox.Draw(); 
     }
    if(inputboxS.IsEnteringInput()){
          
            inputboxS.Draw(); 
     }


 
          

        if(IsKeyPressed(KEY_B)){
           currentscreen = screenStack.top();
           break;
        }

        if(preorder){
            TraversalOrder.clear();
            mytree.TraversePreOrder();
            highlightTraverse = true;  
        }
          if(inorder){
            TraversalOrder.clear();
            mytree.TraverseInOrder();
            highlightTraverse = true;  
        }
          if(postorder){
            TraversalOrder.clear();
            mytree.TraversePostOrder();
            highlightTraverse = true;  
        }
          if(levelorder){
            TraversalOrder.clear();
            mytree.LevelOrderTraverse();
            highlightTraverse = true;  
        }

        if(highlightTraverse){
       
            highlightTraverse = false;
            mytree.HighlightTraversal();
             if(std::find(TraversalOrder.begin(),TraversalOrder.end(),data) == TraversalOrder.end()){
                highlightmessage = true; 
             }else{
                highlightmessage = false;
            }

            
        }
        if(highlightmessage){
            DrawText("Element Not Found",500,60,20,RED);
        } 
       

        EndDrawing();

    }


}
