// Sumeed_Jawad_Kanwar_22i2651
// Maleek_Hussain_Ali_22i1526

#include "GraphNode.h"
#include "Stack.h"
#include "Queue.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Heap.h"

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

class Maze
{
    int width;
    int length;
    GraphNode **maze;
    Queue<Obstacle> obstacles;
    Heap pointsHeap;
    uint64_t start, end;
    // Function to get the current time in seconds since the epoch
    int gettime()
    {
        // Get the current time using chrono library
        // Convert the time duration to seconds and return the count
        return chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
    }

    // Function to display seconds in minutes and seconds format
    void DisplaySecondsInMinutes(int seconds)
    {
        // Calculate the number of minutes from seconds
        int minutes = seconds / 60;

        // Calculate the remaining seconds after converting to minutes
        seconds = seconds % 60;

        // Display the result
        cout << minutes << " minutes and " << seconds << " seconds";
    }

    // Function to process an obstacle
    Obstacle processObstacle()
    {
        // Check if the obstacles queue is not empty
        if (!obstacles.isEmpty())
        {
            // Dequeue an obstacle from the obstacles queue
            Obstacle obstacle = obstacles.dequeue();

            // Return the dequeued obstacle
            return obstacle;
        }
        else
        {
            // If the obstacles queue is empty, create a default obstacle with type "None"
            Obstacle obstacle;
            obstacle.setType("None");

            // Return the default obstacle
            return obstacle;
        }
    }
    
    void generateObstacle(int x, int y)
    {
        // Seed the random number generator with a time-based seed
        random_device rd;
        mt19937 gen(rd());

        // Create a uniform distribution for integers in the specified range
        uniform_int_distribution<int> distribution(0, 2);

        // generate 20% obstacles of the total number of nodes
        int totalNodes = x * y;
        int numObstacles = totalNodes * 0.5;
        for (int i = 0; i < numObstacles; i++)
        {
            Obstacle obstacle;
            int random = distribution(gen);
            if (random == 0)
            {
                obstacle.setType("Obstacle");
            }
            else if (random == 1)
            {
                obstacle.setType("Oil Spill");
            }
            else
            {
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
        // deleteMaze();
        maze = nullptr;

        width = x;
        length = y;
        maze = new GraphNode *[y];
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

                if (distribution(gen) == 1 || distribution(gen) == 4)
                {
                    /* obstacle queue operations */
                    Obstacle obstacle = processObstacle();

                    if (obstacle.getType() == "None")
                    {
                        return;
                    }

                    if (obstacle.getType() == "Obstacle")
                    {
                        maze[i][j].setObstacle(true);
                    }
                    else if (obstacle.getType() == "Oil Spill")
                    {
                        maze[i][j].setOilSpillObstacle(true);
                    }
                    else
                    {
                        maze[i][j].setDebrisObstacle(true);
                    }

                    maze[i][j].setWeight(100);
                }
                else if (distribution(gen) == 2)
                {
                    int random = rand() % 3 + 1;
                    if (random == 1)
                    {
                        maze[i][j].setCoin50(true);
                    }
                    else if (random == 2)
                    {
                        maze[i][j].setCoin100(true);
                    }
                    else
                    {
                        maze[i][j].setCoin150(true);
                    }
                }
                else if (distribution(gen) == 3)
                {
                    int random = rand() % 10 + 1;

                    // if random is 1 then set trophy true, else do nothing
                    if (random == 1)
                    {
                        maze[i][j].setTrophy(true);
                    }
                }
                else
                {
                    /* do nothing */
                }
            }
        }
    }

    void makeEdges(GraphNode &node)
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

    void printNodeSymbol(GraphNode *mazeNode)
    {
        if (mazeNode->isStart())
        {
            cout << GREEN << " S " << RESET;
        }
        else if (mazeNode->isPath())
        {
            cout << CYAN << " P " << RESET;
        }
        else if (mazeNode->isCar())
        {
            cout << BLUE << " C " << RESET;
        }
        else if (mazeNode->isGoal())
        {
            cout << GREEN << " G " << RESET;
        }
        else if (mazeNode->isObstacle())
        {
            cout << RED << " O " << RESET;
        }
        else if (mazeNode->isDebrisObstacle())
        {
            cout << RED << " D " << RESET;
        }
        else if (mazeNode->isOilSpillObstacle())
        {
            cout << RED << " S " << RESET;
        }
        else if (mazeNode->isCoin50())
        {
            cout << YELLOW << "50 " << RESET;
        }
        else if (mazeNode->isCoin100())
        {
            cout << YELLOW << "100" << RESET;
        }
        else if (mazeNode->isCoin150())
        {
            cout << YELLOW << "150" << RESET;
        }
        else if (mazeNode->isTrophy())
        {
            cout << MAGENTA << " T " << RESET;
        }
        else
        {
            cout << " + ";
        }
    }
        
    // Function to display the maze structure visually
    void displayMaze()
    {
        // Iterate through each row (j) of the maze
        for (int j = 0; j < length; j++)
        {
            // Display horizontal symbols for each node in the row
            for (int i = 0; i < width; i++)
            {
                // Print the symbol for the current node
                printNodeSymbol(&maze[i][j]);

                // Get the neighbors of the current node
                Node<GraphNode *> *traverse = maze[i][j].getNeighbors();

                // If there are no neighbors, print empty space
                if (traverse == nullptr)
                {
                    cout << "     ";
                }

                // Iterate through the neighbors and display horizontal edges
                while (traverse != nullptr)
                {
                    if (traverse->data->getX() == i + 1 && traverse->data->getY() == j)
                    {
                        cout << "-----";
                        break;
                    }

                    // If it's the last neighbor, print empty space
                    if (traverse->next == nullptr)
                    {
                        cout << "     ";
                    }

                    traverse = traverse->next;
                }
            }

            // Move to the next line for the second part of the cell representation
            cout << endl;

            // Display vertical symbols and edges for each node in the row
            for (int r = 0; r < width; r++)
            {
                // Check if it's the last row
                if (j == length - 1)
                {
                    break;
                }

                // Get the neighbors of the current node
                Node<GraphNode *> *traverse = maze[r][j].getNeighbors();

                // If there are no neighbors, print empty space
                if (traverse == nullptr)
                {
                    cout << "   "
                         << "\t";
                }

                // Iterate through the neighbors and display vertical edges
                while (traverse != nullptr)
                {
                    if (traverse->data->getX() == r && traverse->data->getY() == j + 1)
                    {
                        cout << " | "
                             << "\t";
                        break;
                    }

                    // If it's the last neighbor, print empty space
                    if (traverse->next == nullptr)
                    {
                        cout << "   "
                             << "\t";
                    }

                    traverse = traverse->next;
                }
            }

            // Move to the next line for the next row
            cout << endl;
        }
    }

    void addEdge(GraphNode *node1, GraphNode *node2)
    {
        node1->addNeighbor(node2);
        node2->addNeighbor(node1);
    }

    GraphNode *getCarNode()  // returns pointer to car node
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

    GraphNode *getGoalNode()  // returns pointer to goal node
    {
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (maze[i][j].isGoal())
                {
                    return &maze[i][j];
                }
            }
        }
        return nullptr;
    }

    GraphNode getCarNodeObject()  // returns car node object
    {
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (maze[i][j].isCar())
                {
                    return maze[i][j];
                }
            }
        }
        return GraphNode(-1, -1);
    }

    GraphNode getGoalNodeObject()  // returns goal node object
    {
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (maze[i][j].isGoal())
                {
                    return maze[i][j];
                }
            }
        }
        return GraphNode(-1, -1);
    }

    // Function to check if a path exists from the start node to the goal node in the maze
    bool pathExists(bool isfirst = true)
    {
        // Static variables to store run_once flag, start and goal coordinates
        static int run_once, x_start, y_start, x_goal, y_goal;

        // If it's the first time running the function, prompt the user for start and goal coordinates
        if (isfirst == true)
        {
            cout << endl
                 << "Enter Start x and y coordinates: ";
            cin >> x_start >> y_start;

            // Validate start coordinates to ensure they are within the maze bounds
            while (x_start >= width || y_start >= length || x_start < 0 || y_start < 0)
            {
                cout << endl
                     << "Invalid start node!" << endl;
                cout << "Enter start node x and y coordinates: ";
                cin >> x_start >> y_start;
            }

            cout << endl
                 << "Enter Goal x and y coordinates: ";
            cin >> x_goal >> y_goal;

            // Validate goal coordinates to ensure they are within the maze bounds
            while (x_goal >= width || y_goal >= length || x_goal < 0 || y_goal < 0)
            {
                cout << endl
                     << "Invalid goal node!" << endl;
                cout << "Enter goal node x and y coordinates: ";
                cin >> x_goal >> y_goal;
            }

            // Increment the run_once flag to avoid re-prompting the user
            run_once++;
        }

        // Set the start node, goal node, and initialize a stack for DFS traversal
        maze[x_start][y_start].setCar(true);
        maze[x_start][y_start].setStart(true);
        maze[x_goal][y_goal].setGoal(true);
        GraphNode *start = &maze[x_start][y_start];
        GraphNode *goal = &maze[x_goal][y_goal];
        Stack<GraphNode *> stack;
        stack.push(start);
        start->setVisited(true);

        // Perform DFS traversal to check for a path from start to goal
        while (!stack.isEmpty())
        {
            GraphNode *current = stack.pop();

            // If the current node is the goal, a path exists
            if (current == goal)
            {
                return true;
            }

            // Explore neighbors and add unvisited neighbors to the stack
            Node<GraphNode *> *neighbors = current->getNeighbors();
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

        // If the stack is empty and goal is not reached, no path exists
        return false;
    }

    // Function to update the state of a given graph node based on the type of node and collect game statistics
    bool setNode(GraphNode *node, float &point, int &coins, int &trophies, List<Coin> &coinsList, List<Trophy> &trophiesList, GraphNode *CarNode)
    {
        // Check the type of the node and update game parameters accordingly

        // Handle obstacle nodes
        if (node->isObstacle())
        {
            point -= 10;
            obstacles.enqueue(Obstacle("Obstacle"));
            node->setObstacle(false);
        }
        // Handle debris obstacle nodes
        else if (node->isDebrisObstacle())
        {
            point -= 5;
            obstacles.enqueue(Obstacle("Debris"));
            node->setDebrisObstacle(false);
        }
        // Handle oil spill obstacle nodes
        else if (node->isOilSpillObstacle())
        {
            point -= 2;
            obstacles.enqueue(Obstacle("Oil Spill"));
            node->setOilSpillObstacle(false);
        }
        // Handle coin nodes with different values
        else if (node->isCoin50())
        {
            point += 5;
            coins += 50;
            coinsList.push_back(Coin(50));
            node->setCoin50(false);
        }
        else if (node->isCoin100())
        {
            point += 5;
            coins += 100;
            coinsList.push_back(Coin(100));
            node->setCoin100(false);
        }
        else if (node->isCoin150())
        {
            point += 5;
            coins += 150;
            coinsList.push_back(Coin(150));
            node->setCoin150(false);
        }
        // Handle trophy nodes
        else if (node->isTrophy())
        {
            point += 100;
            coins += 250;
            trophies++;
            trophiesList.push_back(Trophy(250));
            node->setTrophy(false);
        }
        // Handle goal node
        else if (node->isGoal())
        {
            point += 1000;
            coins += 250;
            trophies++;
            end = gettime();

            // Display game completion statistics
            cout << endl
                 << "You won the game!" << endl;
            cout << endl
                 << "Game Statistics: " << endl;
            cout << endl
                 << "Points: " << point - (end - start);
            pointsHeap.insert(point - (end - start));
            cout << endl
                 << "Coins: " << coins;
            cout << endl
                 << "Trophies: " << trophies << endl;
            cout << endl
                 << "Total time taken: ";
            DisplaySecondsInMinutes(end - start);
            cout << endl
                 << "Coins List: " << endl;

            // Display collected coins
            Node<Coin> *coin_traverse = coinsList.getHead();
            while (coin_traverse != nullptr)
            {
                cout << coin_traverse->data.getValue() << " ";
                coin_traverse = coin_traverse->next;
            }
            cout << endl
                 << "Trophies List: " << endl;

            // Display collected trophies
            Node<Trophy> *trophy_traverse = trophiesList.getHead();
            while (trophy_traverse != nullptr)
            {
                cout << trophy_traverse->data.getValue() << " ";
                trophy_traverse = trophy_traverse->next;
            }

            // Update leaderboard file with the player's score
            fstream outfile;
            outfile.open("Leaderboard.txt", ios::app);
            outfile << point - (end - start) << endl;
            outfile.close();

            // Display leaderboard scores
            fstream infile;
            infile.open("Leaderboard.txt", ios::in);
            int points;
            while (infile >> points)
            {
                cout << endl
                     << "Points: " << points << endl;
                pointsHeap.insert(points);
            }
            this_thread::sleep_for(chrono::milliseconds(3500));
            infile.close();

            // Update leaderboard file with sorted scores
            fstream outfile1;
            outfile1.open("Leaderboard.txt", ios::out | ios::trunc);
            while (pointsHeap.isEmpty() != true)
            {
                outfile1 << pointsHeap.remove() << endl;
            }
            outfile1.close();

            // Indicate that a path to the goal was found
            return true;
        }
        // Handle other types of nodes
        else
        {
            point += 5;
        }

        // Update the car position in the maze
        CarNode->setCar(false);
        node->setCar(true);

        // Indicate that no path to the goal was found
        return false;
    }

    void manualMode()
    {
        float point = 0;
        int coins = 0;
        int trophies = 0;
        char key;
        List<Coin> coinsList;
        List<Trophy> trophiesList;
        bool isfirst = true;

        while (!pathExists(isfirst))
        {
            generateMaze(width, length);
            isfirst = false;
        }
        system("cls");
        displayMaze();

        start = gettime();
        while (true)
        {
            GraphNode *carNode = getCarNode();
            // Display carNode neighbors
            Node<GraphNode *> *neighbors = carNode->getNeighbors();
            while (neighbors != nullptr)
            {
                neighbors = neighbors->next;
            }
            key = _getch(); // Get the pressed key
            system("cls");

            // Print the ASCII value of the pressed key
            if (key == 72)
            {
                /* Up key */
                Node<GraphNode *> *neighbors = carNode->getNeighbors();
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getY() == carNode->getY() - 1 && neighbors->data->getX() == carNode->getX())
                    {
                        bool toreturn = setNode(neighbors->data, point, coins, trophies, coinsList, trophiesList, carNode);
                        if (toreturn)
                        {
                            return;
                        }
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 75)
            {
                /* Left key */
                Node<GraphNode *> *neighbors = carNode->getNeighbors();
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getX() == carNode->getX() - 1 && neighbors->data->getY() == carNode->getY())
                    {
                        bool toReturn = setNode(neighbors->data, point, coins, trophies, coinsList, trophiesList, carNode);
                        if (toReturn)
                        {
                            return;
                        }
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 77)
            {
                /* Right key */
                Node<GraphNode *> *neighbors = carNode->getNeighbors();
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getX() == carNode->getX() + 1 && neighbors->data->getY() == carNode->getY())
                    {
                        bool toReturn = setNode(neighbors->data, point, coins, trophies, coinsList, trophiesList, carNode);
                        if (toReturn) {
                            return;
                        }
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 80)
            {
                /* Down key */
                Node<GraphNode *> *neighbors = carNode->getNeighbors();
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getY() == carNode->getY() + 1 && neighbors->data->getX() == carNode->getX())
                    {
                        bool toReturn = setNode(neighbors->data, point, coins, trophies, coinsList, trophiesList, carNode);
                        if (toReturn) {
                            return;
                        }
                        break;
                    }
                    neighbors = neighbors->next;
                }
            }
            else if (key == 'p')
            {
                int choice = 0;
                while (choice != 1)
                {
                    cout << endl
                         << "Game paused!";
                    cout << endl
                         << "1. Resume";
                    cout << endl
                         << "2. Exit";
                    cin >> choice;

                    if (choice == 2)
                    {
                        return;
                    }
                }
            }

            if (key == 27) // If the Esc key is pressed, exit the loop
                break;

            cout << endl
                 << "Points: " << point;
            cout << endl
                 << "Coins: " << coins;
            cout << endl
                 << "Trophies: " << trophies << endl;
            displayMaze();
        }
    }

    void printmazeweight()
    {
        for (int j = 0; j < length; j++)
        {

            for (int i = 0; i < width; i++)
            {
                cout << maze[i][j].getWeight() << " ";
            }
            cout << endl;
        }
    }

    // Function: shortestpath
    // Description: Finds the shortest path from the starting node (car node) to the goal node in a graph.
    // Returns: A stack of GraphNode pointers representing the shortest path from start to goal.
    Stack<GraphNode *> shortestpath()
    {
        // Initialize start and goal nodes.
        GraphNode *start = getCarNode();
        GraphNode *goal = getGoalNode();

        // Initialize queue for breadth-first search.
        Queue<GraphNode *> queue;
        queue.enqueue(start);
        start->setWeight(0);

        // Use an object instead of a pointer for tracking visited nodes.
        List<GraphNode *> check;

        // Breadth-first search to calculate node weights.
        while (!queue.isEmpty())
        {
            // Process the current node.
            GraphNode *current = queue.dequeue();
            Node<GraphNode *> *neighbors = current->getNeighbors();

            while (neighbors != nullptr)
            {
                // Calculate new weights based on node types.
                int newWeight;
                if (neighbors->data->isCoin50())
                {
                    newWeight = current->getWeight() + 4;
                }
                // ... (similar calculations for other node types)

                // Update node weight if a shorter path is found.
                if (newWeight < neighbors->data->getWeight())
                {
                    neighbors->data->setWeight(newWeight);
                }

                // Enqueue unvisited neighbors and mark them as visited.
                if (!check.search(neighbors->data))
                {
                    queue.enqueue(neighbors->data);
                    check.push_back(neighbors->data);
                }

                neighbors = neighbors->next;
            }
        }

        // Reconstruct the path from goal to start using a stack.
        Stack<GraphNode *> stack;
        GraphNode *current = goal;

        // Use a separate list to track visited nodes during path reconstruction.
        List<GraphNode *> check1;

        while (current != start)
        {
            // Push current node onto the stack.
            stack.push(current);
            check1.push_back(current);
            Node<GraphNode *> *neighbors = current->getNeighbors();

            // Traverse neighbors to find the next node in the path.
            while (neighbors != nullptr)
            {
                if (neighbors->data->getWeight() < current->getWeight() && !check1.search(neighbors->data))
                {
                    current = neighbors->data;
                    break;
                }
                neighbors = neighbors->next;

                // If no suitable neighbor is found, pop from the stack.
                if (neighbors == nullptr)
                {
                    current = stack.pop();
                }
            }
        }

        // Return the stack containing the shortest path.
        return stack;
    }

    // Function to simulate an automatic mode of the game, navigating the car through the maze
    void autoMode()
    {
        // Initialize variables for game statistics
        float point = 0;
        int coins = 0;
        int trophies = 0;
        List<Coin> coinsList;
        List<Trophy> trophiesList;

        // Get the starting node of the car and calculate the shortest path using Dijkstra's algorithm
        GraphNode temp = getCarNodeObject();
        Stack<GraphNode *> stack = shortestpath();

        // Clear the car and set the path flag for the starting node
        temp.setCar(false);
        temp.setPath(true);

        // Process each node in the shortest path
        while (!stack.isEmpty())
        {
            // Move the car to the next node in the path
            GraphNode *current = stack.pop();
            current->setCar(true);

            // Pause for visualization (500 milliseconds) and clear the console screen
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");

            // Process the content of the current node and update game statistics
            if (current->isObstacle())
            {
                point -= 10;
                obstacles.enqueue(Obstacle("Obstacle"));
                current->setObstacle(false);
            }
            else if (current->isOilSpillObstacle())
            {
                point -= 2;
                obstacles.enqueue(Obstacle("Oil Spill"));
                current->setObstacle(false);
            }
            else if (current->isDebrisObstacle())
            {
                point -= 5;
                obstacles.enqueue(Obstacle("Debris"));
                current->setDebrisObstacle(false);
            }
            else if (current->isCoin50())
            {
                point += 5;
                coins += 50;
                coinsList.push_back(Coin(50));
                current->setCoin50(false);
            }
            else if (current->isCoin100())
            {
                point += 5;
                coins += 100;
                coinsList.push_back(Coin(100));
                current->setCoin100(false);
            }
            else if (current->isCoin150())
            {
                point += 5;
                coins += 150;
                coinsList.push_back(Coin(150));
                current->setCoin150(false);
            }
            else if (current->isTrophy())
            {
                point += 1000;
                coins += 250;
                trophies++;
                trophiesList.push_back(Trophy(250));
                current->setTrophy(false);
            }
            else
            {
                point += 5;
            }

            // Display the updated maze with the current position of the car and path
            displayMaze();

            // Clear the car flag and set the path flag for the current node
            current->setCar(false);
            current->setPath(true);
        }

        // Clear the console screen
        system("cls");

        // Finalize game statistics for reaching the goal
        point += 1000;
        coins += 250;
        trophies++;

        // Display the final game statistics
        cout << endl
             << "Game Statistics: " << endl;
        cout << endl
             << "Points: " << point;
        cout << endl
             << "Coins: " << coins;
        cout << endl
             << "Trophies: " << trophies << endl;

        // Display the list of collected coins
        cout << endl
             << "Coins List: " << endl;
        Node<Coin> *coin_traverse = coinsList.getHead();
        while (coin_traverse != nullptr)
        {
            cout << coin_traverse->data.getValue() << " ";
            coin_traverse = coin_traverse->next;
        }

        // Display the list of collected trophies
        cout << endl
             << "Trophies List: " << endl;
        Node<Trophy> *trophy_traverse = trophiesList.getHead();
        while (trophy_traverse != nullptr)
        {
            cout << trophy_traverse->data.getValue() << " ";
            trophy_traverse = trophy_traverse->next;
        }

        // Pause for visualization (2000 milliseconds) before exiting the function
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    void deleteMaze()
    {
        if (maze == nullptr)
        {
            return;
        }

        for (int i = 0; i < length; i++)
        {
            if (maze[i] != nullptr)
            {
                delete[] maze[i];
            }
        }
        delete[] maze;
    }

    ~Maze()
    {
        deleteMaze();
    }

    void LeaderBoard()
    {
        fstream outfile;
        outfile.open("Leaderboard.txt", ios::app);
        outfile.close();

        fstream infile;
        infile.open("Leaderboard.txt", ios::in);
        int points;
        while (infile >> points)
        {
            cout << endl
                 << "Points: " << points << endl;
        }
        infile.close();
    }
};