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

    std::cout << node->data;
    TraversePre(node->left_node); // Left
    TraversePre(node->right_node);

}
void Tree::TraversePreOrder(){
    this->TraversePre(this->root_node);
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
