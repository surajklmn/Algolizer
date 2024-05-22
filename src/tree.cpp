#include "tree.hpp"
#include <algorithm>
#include <iostream>
#include <raylib.h>
 
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

    std::cout << node->data << std::endl;
    TraversePre(node->left_node); // Left
    TraversePre(node->right_node);

}
void Tree::TraverseIn(Node* node){
   if(node == nullptr) return;
   TraverseIn(node->left_node);
   std::cout << node->data << std::endl;
   TraverseIn(node->right_node);
}

void Tree::TraversePos(Node* node){
    if(node == nullptr) return;
    TraversePos(node->left_node);
    TraversePos(node->right_node);
    std::cout << node->data << std::endl; 
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
    mytree.LevelOrderTraverse();

    SetTargetFPS(60); 

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tree Visualiz",20,30,20,GRAY);
        EndDrawing();
    }
}
