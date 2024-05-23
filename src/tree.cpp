#include "tree.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <raylib.h>
#include <raygui/raygui.h>
#include <map>
#include <thread>

bool highlightTraverse = false;
std::unordered_map<int,Node*> nodeposition;
std::vector<int> TraversalOrder;
void Tree::InsertNode(int data){
    Node* data_node = new Node(data);
    if(root_node == nullptr){
        root_node = data_node;
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
            std::cout << node_value << std::endl;
        }
    }


}
void DrawTree(Node* node,int startingX,int startingY,int spacing){
    int Radius = 30;
    int level_height = Radius+60;
   
        
    Vector2 linestart_Left = {static_cast<float>(startingX-Radius),static_cast<float>(startingY)};
    Vector2 lineend_Left = {static_cast<float>(startingX-spacing-Radius),static_cast<float>(startingY+level_height)};
    
    Vector2 linestart_Right = {static_cast<float>(startingX+Radius),static_cast<float>(startingY)};
    Vector2 lineend_Right = {static_cast<float>(startingX+spacing+Radius),static_cast<float>(startingY+level_height)};
    Color linecolor = DARKGRAY;


   
    if(node == nullptr) return;
    nodeposition.insert({node->data,node});
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



// Public Functions
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





void Tree::UpdateAtCoordinate(){
    for(int item : TraversalOrder){
   
        nodeposition[item]->color = BLUE;
        BeginDrawing();
        DrawTreeStructure();
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        nodeposition[item]->color = DARKGRAY;
      
    }
}


// Visualizer Function
void RunTreeVisualizer(){
    
    Tree mytree;
    mytree.InsertNode(7);
    mytree.InsertNode(4);
    mytree.InsertNode(9);
    mytree.InsertNode(1);
     mytree.InsertNode(6);
     mytree.InsertNode(8);
     mytree.InsertNode(10);
    mytree.InsertNode(3);



    //--------- Gui Constants
    const int screenwidth = 1024;
    const int screenheight = 768;
   

    
    SetTargetFPS(60); 
    //---------------Traversal Buttons Dimensions

    Rectangle buttonPre = {20,20,150,30};
    Rectangle buttonIn = {20,60,150,30};
    Rectangle buttonPos = {20,100,150,30};
    Rectangle buttonLev = {20,140,150,30};

    // ----------------- Instruction texts
    std::vector<std::string> instruction_texts; 
    instruction_texts.push_back("Tree Type: Binary Tree");
    instruction_texts.push_back("Press 'Enter' To Insert Value");
     
    // ---------------------- Set Gui Configurations
    GuiSetStyle(DEFAULT,TEXT_SIZE,12);
    SetWindowSize(screenwidth,screenheight);
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
        mytree.DrawTreeStructure();
        if(highlightTraverse){
        mytree.UpdateAtCoordinate();
        highlightTraverse = false;
        }
        mytree.DrawTreeStructure();
        if(preorder){
            TraversalOrder.clear();
            mytree.TraversePreOrder();
            highlightTraverse = true;  
        }
      
        
        // ---------- Render Instruction Texts
        
        for(const std::string& text: instruction_texts){
        
            DrawText(text.c_str(),x_coordinateText,y_coordinateText,15,GRAY);
            y_coordinateText +=20; 
        }
       
       
        EndDrawing();

    }


}
