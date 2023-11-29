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
            bool horizontal;
            bool vertical;
            for (int j = 0; j < length; j++)
            {
                horizontal = false;
                vertical = false;
                
                
                for (int i = 0; i < width; i++)
                {
                    cout << maze[i][j].getX() << "," << maze[i][j].getY();
                    Node<GraphNode *>* traverse = maze[i][j].getNeighbors();
                    while (traverse != nullptr) {
                        
                        
                        if (traverse->data->getX() == i + 1 && traverse->data->getY() == j) {
                            cout << "-----";
                            horizontal = true;
                            break;
                        }
                        if (traverse->next == nullptr) {
                            cout << "     ";
                        }
                        traverse = traverse->next;
                    }
                }
                cout << endl;
                
                
                for (int r = 0; r < width; r++) {
                    Node<GraphNode *> *traverse = maze[j][r].getNeighbors();
                    while (traverse != nullptr) {
                        
                        
                        if (traverse->data->getX() == j && traverse->data->getY() == r + 1)
                        {
                            cout << " | " << "\t";
                            vertical = true;
                            break;
                        }
                        if (traverse->next == nullptr) {
                            cout << "   " << "\t";
                        }
                        traverse = traverse->next;
                    }
                }
                cout << endl;
                
                
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