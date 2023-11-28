#include "GraphNode.h"

class Maze {
    int X;
    int Y;
    GraphNode** maze;

public:
    void generateMaze(int x, int y) {
        X = x;
        Y = y;
        maze = new GraphNode * [x];
        for (int i = 0; i < x; i++) {
            maze[i] = new GraphNode[y];
        }
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++)
            {
                maze[i][j] = GraphNode(i, j);
                makeEdges(maze[i][j]);
            }
        }
    }

    void makeEdges(GraphNode& node) {
        int x = node.getX();
        int y = node.getY();
        if (x > 0) {
            addEdge(&node, &maze[x - 1][y]);
        }
        if (x < X - 1) {
            addEdge(&node, &maze[x + 1][y]);
        }
        if (y > 0) {
            addEdge(&node, &maze[x][y - 1]);
        }
        if (y < Y - 1) {
            addEdge(&node, &maze[x][y + 1]);
        }
    }

    void addEdge(GraphNode* node1, GraphNode* node2) {
        node1->addNeighbor(node2);
        node2->addNeighbor(node1);
    }

    void addEdge(int x1, int y1, int x2, int y2) {
        maze[x1][y1].addNeighbor(&maze[x2][y2]);
        maze[x2][y2].addNeighbor(&maze[x1][y1]);
    }

};