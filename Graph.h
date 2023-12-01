#include "GraphNode.h"
#include "Stack.h"
#include "Queue.h"
#include "Obstacle.h"
#include "Coin.h"

#include <climits>
#include <random>
#include <conio.h>
#include <cstdlib>

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
    Queue<Obstacle> obstacles;

    Obstacle processObstacle()
    {
        if (!obstacles.isEmpty()) {
            Obstacle obstacle = obstacles.dequeue();
            return obstacle;
        }
    }

    void generateObstacle(int x, int y) {
        // Seed the random number generator with a time-based seed
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform distribution for integers in the specified range
        uniform_int_distribution<int> distribution(0, 2);

        // generate 20% obstacles of the total number of nodes
        int totalNodes = x * y;
        int numObstacles = totalNodes * 0.2;
        for (int i = 0; i < numObstacles; i++) {
            Obstacle obstacle;
            int random = distribution(gen);
            if (random == 0) {
                obstacle.setType("Obstacle");
            }
            else if (random == 1) {
                obstacle.setType("Oil Spill");
            }
            else {
                obstacle.setType("Debris");
            }
            obstacles.enqueue(obstacle);
        }
    }

public:
    void generateMaze(int x, int y)
    {
        // Seed the random number generator with a time-based seed
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform distribution for integers in the specified range
        uniform_int_distribution<int> distribution(1, 5);

        // TODO: Generate obstacles and enqueue them in the obstacles queue
        generateObstacle(x, y);

        width = x;
        length = y;
        maze = new GraphNode * [y];
        for (int i = 0; i < y; i++)
        {
            maze[i] = new GraphNode[x];
        }
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                maze[i][j] = GraphNode(i, j);
            }
        }
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                makeEdges(maze[i][j]);

                if (distribution(gen) == 1)
                {
                    /* obstacle queue operations */
                    Obstacle obstacle = processObstacle();

                    if (obstacle.getType() == "Obstacle") {
                        maze[i][j].setObstacle(true);
                    }
                    else if (obstacle.getType() == "Oil Spill") {
                        maze[i][j].setOilSpillObstacle(true);
                    }
                    else {
                        maze[i][j].setDebrisObstacle(true);
                    }

                    maze[i][j].setWeight(100);
                }
                else if (distribution(gen) == 2)
                {
                    maze[i][j].setBoost(true);
                    maze[i][j].setWeight(1);
                }
                else
                {
                    /* do nothing */
                }
            }
        }

        // Only to test isCar and isGoal
        maze[0][0].setCar(true);
        maze[width - 1][length - 1].setGoal(true);
    }

    void makeEdges(GraphNode& node)
    {
        // Seed the random number generator with a time-based seed
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform distribution for integers in the specified range
        uniform_int_distribution<int> distribution(0, 4);

        int x = node.getX();
        int y = node.getY();
        if (x < width - 1)
        {
            if (distribution(gen) == 1 || distribution(gen) == 2 || distribution(gen) == 3 || distribution(gen) == 4)
            {
                addEdge(&node, &maze[x + 1][y]);
            }
        }
        if (y < length - 1)
        {
            if (distribution(gen) == 1 || distribution(gen) == 2 || distribution(gen) == 3 || distribution(gen) == 4)
            {
                addEdge(&node, &maze[x][y + 1]);
            }
        }
    }

    void printNodeSymbol(GraphNode* mazeNode) {
        if (mazeNode->isCar())
        {
            cout << RED << " C " << RESET;
        }
        else if (mazeNode->isGoal())
        {
            cout << GREEN << " G " << RESET;
        }
        else if (mazeNode->isObstacle())
        {
            cout << YELLOW << " O " << RESET;
        }
        else if (mazeNode->isBoost())
        {
            cout << BLUE << " B " << RESET;
        }
        else
        {
            cout << " + ";
        }
    }

    void displayMaze()
    {
        for (int j = 0; j < length; j++)
        {
                        
            for (int i = 0; i < width; i++)
            {
                printNodeSymbol(&maze[i][j]);
                Node<GraphNode *>* traverse = maze[i][j].getNeighbors();
                if (traverse == nullptr) {
                    cout << "     ";
                }
                while (traverse != nullptr) {
                    if (traverse->data->getX() == i + 1 && traverse->data->getY() == j) {
                        cout << "-----";
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

                Node<GraphNode *> *traverse = maze[r][j].getNeighbors();
                if (traverse == nullptr) {
                    cout << "   " << "\t";
                }
                while (traverse != nullptr) {
                    if (traverse->data->getX() == r && traverse->data->getY() == j + 1)
                    {
                        cout << " | " << "\t";
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

    void addEdge(GraphNode* node1, GraphNode* node2)
    {
        node1->addNeighbor(node2);
        node2->addNeighbor(node1);
    }

    GraphNode* getCarNode()
    {
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (maze[i][j].isCar())
                {
                    return &maze[i][j];
                }
            }
        }
        return nullptr;
    }

    void manualMode()
    {
        char key;
        while (true)
        {
            GraphNode* carNode = getCarNode();
            // Display carNode neighbors
            cout << endl << "Neighbors: ";
            Node<GraphNode *> *neighbors = carNode->getNeighbors();
            while (neighbors != nullptr)
            {
                cout << "(" << neighbors->data->getX() << ", " << neighbors->data->getY() << ") ";
                neighbors = neighbors->next;
            }
            key = _getch(); // Get the pressed key
            system("cls");

            // Print the ASCII value of the pressed key
            if (key == 72)
            {
                /* Up key */
                Node<GraphNode*>* neighbors = carNode->getNeighbors();
                while (neighbors != nullptr) {
                    if (neighbors->data->getY() == carNode->getY() - 1) {
                        carNode->setCar(false);
                        neighbors->data->setCar(true);
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 75)
            {    
                /* Left key */
                Node<GraphNode*>* neighbors = carNode->getNeighbors();
                while (neighbors != nullptr) {
                    if (neighbors->data->getX() == carNode->getX() - 1) {
                        carNode->setCar(false);
                        neighbors->data->setCar(true);
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 77)
            {
                /* Right key */
                Node<GraphNode*>* neighbors = carNode->getNeighbors();
                while (neighbors != nullptr) {
                    if (neighbors->data->getX() == carNode->getX() + 1) {
                        carNode->setCar(false);
                        neighbors->data->setCar(true);
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 80)
            {
                /* Down key */
                Node<GraphNode*>* neighbors = carNode->getNeighbors();
                while (neighbors != nullptr) {
                    if (neighbors->data->getY() == carNode->getY() + 1) {
                        carNode->setCar(false);
                        neighbors->data->setCar(true);
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }

            if (key == 27) // If the Esc key is pressed, exit the loop
                break;

            displayMaze();
        }
    }

    //Function to check if path exists from start to goal:
    bool pathExists()
    {
        GraphNode* start = getCarNode();
        GraphNode* goal = &maze[width - 1][length - 1];
        Stack<GraphNode*> stack;
        stack.push(start);
        start->setVisited(true);
        while (!stack.isEmpty())
        {
            GraphNode* current = stack.pop();
            if (current == goal)
            {
                return true;
            }
            Node<GraphNode*>* neighbors = current->getNeighbors();
            while (neighbors != nullptr)
            {
                if (!neighbors->data->isVisited())
                {
                    stack.push(neighbors->data);
                    neighbors->data->setVisited(true);
                }
                neighbors = neighbors->next;
            }
        }
        return false;
    }

    //function to find the shortest distance to the goal using Dijkstra's algorithm and store it in adjecency list of the graph nodes:
    void dijkstraAlgorithm()
{
    GraphNode* start = getCarNode();
    GraphNode* goal = &maze[width - 1][length - 1];
    Queue<GraphNode*> queue;
    queue.enqueue(start);
    start->setWeight(0);

    cout << "Queue starts: " << endl;
    while (!queue.isEmpty())
    {
        GraphNode* current = queue.dequeue();
        Node<GraphNode*>* neighbors = current->getNeighbors();

        while (neighbors != nullptr)
        {
            int newWeight = current->getWeight() + neighbors->data->getWeight();

            if (newWeight < neighbors->data->getWeight())
            {
                neighbors->data->setWeight(newWeight);
                queue.enqueue(neighbors->data);
            }

            neighbors = neighbors->next;
        }
    }
    cout << endl << "Goal weight: " << goal->getWeight() << endl;
    cout << endl << "Queue ends: " << endl;
    // Store the shortest path in the adjacency list of the graph nodes:
    cout << endl << "Stack starts: " << endl;
    Stack<GraphNode*> stack;
    stack.push(goal);

    while (goal != start)
{
    Node<GraphNode*>* neighbors = goal->getNeighbors();
    int minWeight = INT_MAX;
    GraphNode* nextNode = nullptr;

    while (neighbors != nullptr)
    {
        int weight = neighbors->data->getWeight();

        if (weight < minWeight)
        {
            minWeight = weight;
            nextNode = neighbors->data;
        }

        neighbors = neighbors->next;
    }

    if (nextNode != nullptr)
    {
        stack.push(nextNode);
        goal = nextNode;
    }
    else
    {
        // Handle the case where no valid neighbor is found.
        // This could be an error condition or an appropriate action.
        break;
    }
}

    cout << endl << "Stack ends: " << endl;
    // Now move the car from start to goal using the adjacency list:
    GraphNode* current = start;

    while (current != goal)
    {
        Node<GraphNode*>* adj = current->getAdj();

        while (adj != nullptr)
        {
            if (adj->data->getWeight() == current->getWeight() - adj->data->getWeight())
            {
                current->setCar(false);
                adj->data->setCar(true);
                current = adj->data;
                break;
            }

            adj = adj->next;
        }

        displayMaze();
    }
}




};