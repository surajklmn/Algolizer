// graph.hpp

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <raylib.h>

class Graph {
public:
    Graph();
    void AddNode(int data);
    void AddEdge(int from, int to);
    void DrawGraphStructure(bool highlight = false);
    void BFS(int start);
    void DFS(int start);

private:
    struct Node {
        int data;
        std::vector<Node*> neighbors;
        Color color;
        Vector2 position;

        Node(int d) : data(d), color(DARKGRAY), position({0, 0}) {}
    };

    std::unordered_map<int, Node*> nodes;
    std::vector<int> traversalOrder;
    void DrawGraph(bool highlight);
    void HighlightTraversal();
};

#endif // GRAPH_HPP

