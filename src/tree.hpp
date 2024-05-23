#pragma once
#include <vector>
#include <raylib.h>
struct Node{
    int data;
    Node* left_node;
    Node* right_node;
    Color color;
    Node(int data): data(data),left_node(nullptr),right_node(nullptr),color(DARKGRAY){}

};

class Tree{

public:
    Tree(): root_node(nullptr){}
    void InsertNode(int data);
    void Deletion();
    void TraversePreOrder();
    void TraverseInOrder();
    void TraversePostOrder();
    void LevelOrderTraverse();
    std::vector<int> NodeAtDistance(int distance);
    const int getHeight();
    void DrawTreeStructure();
       void UpdateAtCoordinate();

private:
    void TraverseIn(Node* root_node);
    void TraversePre(Node* root_node);
    void TraversePos(Node* root_node);
    int CalculateTreeHeight(Node* node);
    void GetNodeAtDistance(Node* node,int distance,std::vector<int>& data);
    void TraverseLevel(Node* node);
 
    Node* root_node;

};

void RunTreeVisualizer();
