#include "GraphNode.h"
#include <random>

// ANSI escape codes for text colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

class Maze {
    int width;
    int length;
    GraphNode** maze;

public:
    void generateMaze(int x, int y) {
        // Seed the random number generator with a time-based seed
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform distribution for integers in the specified range
        uniform_int_distribution<int> distribution(1, 5);

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

                if (distribution(gen) == 1) {
                    maze[i][j].setObstacle(true);
                }
                else if (distribution(gen) == 2) {
                    maze[i][j].setBoost(true);
                }
                else {
                    /* do nothing */
                }
            }
        }

        // Only to test isCar and isGoal
        maze[0][0].setCar(true);
        maze[width - 1][length - 1].setGoal(true);
    }

    void makeEdges(GraphNode& node) {
        // Seed the random number generator with a time-based seed
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform distribution for integers in the specified range
        uniform_int_distribution<int> distribution(0, 3);

        int x = node.getX();
        int y = node.getY();
        if (x < width - 1) {
            if (distribution(gen) == 1 || distribution(gen) == 2 || distribution(gen) == 3) {
                addEdge(&node, &maze[x + 1][y]);
            }
        }
        if (y < length - 1) {
            if (distribution(gen) == 1 || distribution(gen) == 2 || distribution(gen) == 3)
            {
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
                if (maze[i][j].isCar()) {
                    cout << RED << " C " << RESET;
                }
                else if (maze[i][j].isGoal()) {
                    cout << GREEN << " G " << RESET;
                }
                else if (maze[i][j].isObstacle()) {
                    cout << YELLOW << " O " << RESET;
                }
                else if (maze[i][j].isBoost()) {
                    cout << BLUE << " B " << RESET;
                }
                else {
                    cout << " + ";
                }
                Node<GraphNode *>* traverse = maze[i][j].getNeighbors();
                if (traverse == nullptr) {
                    cout << "     ";
                }
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
                if (j == length - 1) {
                    break;
                }

                Node<GraphNode *> *traverse = maze[j][r].getNeighbors();
                if (traverse == nullptr) {
                    cout << "   " << "\t";
                }
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

    void printMazeNode(GraphNode node) {
        // if (node.isCar()) {
        //     cout << RED << "  C  " << RESET;
        // }
        // else if (node.isGoal()) {
        //     cout << GREEN << "  G  " << RESET;
        // }
        // else if (node.isObstacle()) {
        //     cout << YELLOW << "  O  " << RESET;
        // }
        // else {
        //     cout << "  0  ";
        // }
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