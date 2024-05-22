#pragma once

struct Node{
    int data;
    Node* left_node;
    Node* right_node;

    Node(int data): data(data),left_node(nullptr),right_node(nullptr){}

};

class Tree{

public:
    Tree(): root_node(nullptr){}
    void InsertNode(int data);
    void Deletion();
    void TraversePreOrder();
    void TraverseInOrder();
    void TraversePostOrder();

private:
    void TraverseIn(Node* root_node);
    void TraversePre(Node* root_node);
    void TraversePos(Node* root_node);
    Node* root_node;

};

void RunTreeVisualizer();
