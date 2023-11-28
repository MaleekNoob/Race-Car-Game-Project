#include "GraphNode.h"
#include <cstdlib>

class Maze {
    int width;
    int length;
    GraphNode** maze;

public:
    void generateMaze(int x, int y) {
        width = x;
        length = y;
        maze = new GraphNode * [y];
        for (int i = 0; i < y; i++) {
            maze[i] = new GraphNode[x];
        }
        for (int j = 0; j < length; j++) {
            for (int i = 0; i < width; i++)
            {
                maze[i][j] = GraphNode(i, j);
                makeEdges(maze[i][j]);
            }
        }
    }

    void makeEdges(GraphNode& node) {
        int x = node.getX();
        int y = node.getY();
        if (x < width - 1) {
            if (rand() % 2 == 1) {
                addEdge(&node, &maze[x + 1][y]);
            }
        }
        if (y < length - 1) {
            if (rand() % 2 == 1) {
                addEdge(&node, &maze[x][y + 1]);
            }
        }
    }

    GraphNode** getMaze() {
        return maze;
    }

        void displayMaze()
        {
            for (int j = 0; j < length; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    cout << maze[i][j].getX() << "," << maze[i][j].getY();
                    if (maze[i][j].getNeighbors().find(&maze[i + 1][j])) {
                        cout << "-----";
                    }
                    else {
                        cout << "\t";
                    }

                }
                cout << endl;
                for (int k = 0; k < 2; k++) {
                    for (int r = 0; r < width; r++) {
                        cout << "Checking " << r << "," << j << " and " << r << "," << j + 1 << endl;
                        maze[r][j].getNeighbors().display();

                        // if (maze[r][j].getNeighbors().find(&maze[r][j + 1])) {
                        //     cout << " | " << "\t";
                        // }
                        // else {
                        //     cout << "   " << "\t";
                        // }
                    }
                    cout << endl;
                }
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