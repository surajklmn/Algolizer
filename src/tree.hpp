#pragma once

struct Node{
    int data;
    Node* left_node;
    Node* right_node;
};

class Tree{

public:
   private:
    Tree(): root_node(nullptr){}
    void InsertNode(int data);
    void Deletion();
    void TraverseIn();
    void TraversePre();
    void TraversePos();

private:
    Node* root_node;

};

void RunTreeVisualizer();
