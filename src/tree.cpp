#include "tree.hpp"

#include <iostream>
 
void Tree::InsertNode(int data){
    Node* data_node = new Node(data);
    if(root_node == nullptr){
        root_node = data_node; 
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
            current_node = current_node->left_node;
        }
    }
}


void Tree::TraversePre(Node* node){
    if(node == nullptr) return;

    std::cout << node->data;
    TraversePre(node->left_node); // Left
    TraversePre(node->right_node);

}
