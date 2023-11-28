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
        maze = new GraphNode * [x];
        for (int i = 0; i < x; i++) {
            maze[i] = new GraphNode[y];
        }
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++)
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
            if (rand() % 2 == 1) {
                addEdge(&node, &maze[x - 1][y]);
            }
        }
        if (x < width - 1) {
            if (rand() % 2 == 1) {
                addEdge(&node, &maze[x + 1][y]);
            }
        }
        if (y > 0) {
            if (rand() % 2 == 1) {
                addEdge(&node, &maze[x][y - 1]);
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

    void displayMaze() {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++)
            {
                if (maze[i][j].isObstacle()) {
                    cout << "X";
                    if (maze[i][j].getX() > 0) {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i - 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i - 1][j])) {
                            cout << "----";
                        }
                        else {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getX() < width - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i + 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i + 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getY() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j - 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j - 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    if (maze[i][j].getY() < length - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j + 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j + 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                else if (maze[i][j].isCar()) {
                    cout << "C";
                    if (maze[i][j].getX() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i - 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i - 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getX() < width - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i + 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i + 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getY() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j - 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j - 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    if (maze[i][j].getY() < length - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j + 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j + 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                else if (maze[i][j].isGoal()) {
                    cout << "G";
                    if (maze[i][j].getX() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i - 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i - 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getX() < width - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i + 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i + 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getY() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j - 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j - 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    if (maze[i][j].getY() < length - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j + 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j + 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                else if (maze[i][j].isStart()) {
                    cout << "S";
                    if (maze[i][j].getX() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i - 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i - 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getX() < width - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i + 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i + 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getY() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j - 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j - 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    if (maze[i][j].getY() < length - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j + 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j + 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                else {
                    if (maze[i][j].getX() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i - 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i - 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    cout << "0";
                    if (maze[i][j].getX() < width - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i + 1][j] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i + 1][j]))
                        {
                            cout << "----";
                        }
                        else
                        {
                            cout << "    ";
                        }
                    }
                    if (maze[i][j].getY() > 0)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j - 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j - 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                    if (maze[i][j].getY() < length - 1)
                    {
                        // traverse through the list of neighbors and if any neighbor is equal to maze[i][j + 1] then print a line
                        if (maze[i][j].getNeighbors().find(&maze[i][j + 1]))
                        {
                            cout << "|";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
            }
            cout << endl << endl;
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