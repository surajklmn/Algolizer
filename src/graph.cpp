#include "raylib.h"
#include <vector>
#include <queue>
#include <stdio.h>
#include "main.h"
#include <stack>
#include "graph.h"
#define NODE_COUNT 6
#define DELAY_TIME 1.0 // Delay time in seconds
extern std::stack<screen> screenStack;
extern screen currentscreen;
// Graph represented as an adjacency matrix (excluding node 0)
int G[NODE_COUNT + 1][NODE_COUNT + 1] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0}
};

// Node positions for tree-like visualization (excluding node 0)
Vector2 nodePositions[NODE_COUNT + 1] = {
    {0, 0},      // Placeholder for node 0
    {400, 100},  // Root node (1)
    {300, 200},  // Level 1
    {500, 200},
    {200, 300},  // Level 2
    {400, 300},
    {600, 300}   // Level 3
};

// Node states
enum NodeState {
    UNVISITED,
    IN_QUEUE,
    PROCESSED
};

NodeState nodeStates[NODE_COUNT + 1] = { UNVISITED };

// Variables for BFS traversal
std::vector<int> bfsOrder;
std::queue<int> q;
int currentIndex = 0;
float timer = 0.0f;

// BFS initialization function
void InitBFS(int start, int n) {
    nodeStates[start] = IN_QUEUE;
    q.push(start);
}

// Function to draw the graph
void DrawGraph() {
    // Draw edges
    for (int i = 1; i <= NODE_COUNT; i++) {
        for (int j = 1; j <= NODE_COUNT; j++) {
            if (G[i][j] == 1) {
                DrawLineV(nodePositions[i], nodePositions[j], DARKGRAY);
            }
        }
    }

    // Draw nodes
    for (int i = 1; i <= NODE_COUNT; i++) {
        Color color;
        switch (nodeStates[i]) {
            case UNVISITED: color = BLUE; break;
            case IN_QUEUE: color = YELLOW; break;
            case PROCESSED: color = GREEN; break;
        }
        DrawCircleV(nodePositions[i], 20, color);
        DrawText(TextFormat("%d", i), nodePositions[i].x - 5, nodePositions[i].y - 10, 20, WHITE);
    }
}

// Main function
void RunGraphVisualizer() {
    InitWindow(800, 600, "Algolizer");
    SetTargetFPS(60);
    // Start BFS from node 4
    InitBFS(1, NODE_COUNT + 1);
    while (!WindowShouldClose()) {
               ClearBackground(RAYWHITE);
        if(IsKeyPressed(KEY_B)){
            currentscreen = screenStack.top();
            break;

        }

        timer += GetFrameTime();

        if (timer >= DELAY_TIME) {
            timer = 0.0f;

            if (!q.empty()) {
                int node = q.front();
                q.pop();
                bfsOrder.push_back(node);
                nodeStates[node] = PROCESSED;

                for (int j = 1; j <= NODE_COUNT; j++) {
                    if (G[node][j] == 1 && nodeStates[j] == UNVISITED) {
                        nodeStates[j] = IN_QUEUE;
                        q.push(j);
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the graph
        DrawGraph();

        EndDrawing();
    }
}

