#include "tree.hpp"

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

void Tree::TraversePreOrder(){
    this->TraversePre(this->root_node);
}

void Tree::TraverseInOrder(){
    this->TraverseIn(this->root_node);
}
void Tree::TraversePostOrder(){
    this->TraversePos(this->root_node);
}

void RunTreeVisualizer(){
   
    Tree mytree;
    mytree.InsertNode(30);
    mytree.TraversePreOrder();


    SetTargetFPS(60); 
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tree Visualiz",20,30,20,GRAY);
        EndDrawing();
    }
}
