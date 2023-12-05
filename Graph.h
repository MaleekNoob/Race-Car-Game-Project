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

class Maze
{
    int width;
    int length;
    GraphNode** maze;
    Queue<Obstacle> obstacles;

    Obstacle processObstacle()
    {
        if (!obstacles.isEmpty())
        {
            Obstacle obstacle = obstacles.dequeue();
            return obstacle;
        }
        else
        {
            Obstacle obstacle;
            obstacle.setType("None");
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

    void printNodeSymbol(GraphNode* mazeNode)
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

    void displayMaze()
    {
        for (int j = 0; j < length; j++)
        {

            for (int i = 0; i < width; i++)
            {
                printNodeSymbol(&maze[i][j]);
                Node<GraphNode*>* traverse = maze[i][j].getNeighbors();
                if (traverse == nullptr)
                {
                    cout << "     ";
                }
                while (traverse != nullptr)
                {
                    if (traverse->data->getX() == i + 1 && traverse->data->getY() == j)
                    {
                        cout << "-----";
                        break;
                    }
                    if (traverse->next == nullptr)
                    {
                        cout << "     ";
                    }
                    traverse = traverse->next;
                }
            }
            cout << endl;

            for (int r = 0; r < width; r++)
            {
                if (j == length - 1)
                {
                    break;
                }

                Node<GraphNode*>* traverse = maze[r][j].getNeighbors();
                if (traverse == nullptr)
                {
                    cout << "   "
                        << "\t";
                }
                while (traverse != nullptr)
                {
                    if (traverse->data->getX() == r && traverse->data->getY() == j + 1)
                    {
                        cout << " | "
                            << "\t";
                        break;
                    }
                    if (traverse->next == nullptr)
                    {
                        cout << "   "
                            << "\t";
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

    GraphNode* getGoalNode()
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

    GraphNode getCarNodeObject()
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

    GraphNode getGoalNodeObject()
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

    bool pathExists(bool isfirst = true)
    {
        static int run_once, x_start, y_start, x_goal, y_goal;
        if (isfirst == true)
        {
            cout << endl
                << "Enter Start x and y coordinates: ";
            cin >> x_start >> y_start;
            while (x_start >= width || y_start >= length || x_start < 0 || y_start < 0)
            {
                cout << endl
                    << "Invalid start node!" << endl;
                cout << endl
                    << "Enter start node x and y components: ";
                cin >> x_start >> y_start;
            }

            cout << endl
                << "Enter Goal x and y coordinates: ";
            cin >> x_goal >> y_goal;
            while (y_goal >= width || y_goal >= length || x_goal < 0 || y_goal < 0)
            {
                cout << endl
                    << "Invalid goal node!" << endl;
                cout << endl
                    << "Enter goal node x and y components: ";
                cin >> x_goal >> y_goal;
            }
            run_once++;
        }
        maze[x_start][y_start].setCar(true);
        maze[x_start][y_start].setStart(true);
        maze[x_goal][y_goal].setGoal(true);
        GraphNode* start = &maze[x_start][y_start];
        GraphNode* goal = &maze[x_goal][y_goal];
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

    void manualMode()
    {
        float point = 0;
        int coins = 0;
        int trophies = 0;
        char key;
        List<Coin> coinsList;
        List<Trophy> trophiesList;
        bool isfirst = true;
        
        while (!pathExists(isfirst)) {
            generateMaze(width, length);
            isfirst = false;
        }
        displayMaze();

        while (true)
        {
            GraphNode* carNode = getCarNode();
            // Display carNode neighbors
            cout << endl
                << "Neighbors: ";
            Node<GraphNode*>* neighbors = carNode->getNeighbors();
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
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getY() == carNode->getY() - 1)
                    {

                        if (neighbors->data->isObstacle())
                        {
                            point -= 10;
                            obstacles.enqueue(Obstacle("Obstacle"));
                            neighbors->data->setObstacle(false);
                        }
                        else if (neighbors->data->isDebrisObstacle())
                        {
                            point -= 5;
                            obstacles.enqueue(Obstacle("Debris"));
                            neighbors->data->setDebrisObstacle(false);
                        }
                        else if (neighbors->data->isOilSpillObstacle())
                        {
                            point -= 2;
                            obstacles.enqueue(Obstacle("Oil Spill"));
                            neighbors->data->setOilSpillObstacle(false);
                        }
                        else if (neighbors->data->isCoin50())
                        {
                            point += 5;
                            coins += 50;
                            coinsList.push_back(Coin(50));
                            neighbors->data->setCoin50(false);
                        }
                        else if (neighbors->data->isCoin100())
                        {
                            point += 5;
                            coins += 100;
                            coinsList.push_back(Coin(100));
                            neighbors->data->setCoin100(false);
                        }
                        else if (neighbors->data->isCoin150())
                        {
                            point += 5;
                            coins += 150;
                            coinsList.push_back(Coin(150));
                            neighbors->data->setCoin150(false);
                        }
                        else if (neighbors->data->isTrophy())
                        {
                            point += 100;
                            coins += 250;
                            trophies++;
                            trophiesList.push_back(Trophy(250));
                            neighbors->data->setTrophy(false);
                        }
                        else if (neighbors->data->isGoal())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;

                            cout << endl
                                << "You won the game!" << endl;
                            cout << endl
                                << "Game Statistics: " << endl;
                            cout << endl
                                << "Points: " << point;
                            cout << endl
                                << "Coins: " << coins;
                            cout << endl
                                << "Trophies: " << trophies << endl;

                            cout << endl
                                << "Coins List: " << endl;
                            Node<Coin>* coin_traverse = coinsList.getHead();
                            while (coin_traverse != nullptr)
                            {
                                cout << coin_traverse->data.getValue() << " ";
                                coin_traverse = coin_traverse->next;
                            }
                            cout << endl
                                << "Trophies List: " << endl;
                            Node<Trophy>* trophy_traverse = trophiesList.getHead();
                            while (trophy_traverse != nullptr)
                            {
                                cout << trophy_traverse->data.getValue() << " ";
                                trophy_traverse = trophy_traverse->next;
                            }
                            return;
                        }
                        else
                        {
                            point += 5;
                        }

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
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getX() == carNode->getX() - 1)
                    {

                        if (neighbors->data->isObstacle())
                        {
                            point -= 10;
                            obstacles.enqueue(Obstacle("Obstacle"));
                            neighbors->data->setObstacle(false);
                        }
                        else if (neighbors->data->isDebrisObstacle())
                        {
                            point -= 5;
                            obstacles.enqueue(Obstacle("Debris"));
                            neighbors->data->setDebrisObstacle(false);
                        }
                        else if (neighbors->data->isOilSpillObstacle())
                        {
                            point -= 2;
                            obstacles.enqueue(Obstacle("Oil Spill"));
                            neighbors->data->setOilSpillObstacle(false);
                        }
                        else if (neighbors->data->isCoin50())
                        {
                            point += 5;
                            coins += 50;
                            coinsList.push_back(Coin(50));
                            neighbors->data->setCoin50(false);
                        }
                        else if (neighbors->data->isCoin100())
                        {
                            point += 5;
                            coins += 100;
                            coinsList.push_back(Coin(100));
                            neighbors->data->setCoin100(false);
                        }
                        else if (neighbors->data->isCoin150())
                        {
                            point += 5;
                            coins += 150;
                            coinsList.push_back(Coin(150));
                            neighbors->data->setCoin150(false);
                        }
                        else if (neighbors->data->isTrophy())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;
                            trophiesList.push_back(Trophy(250));
                            neighbors->data->setTrophy(false);
                        }
                        else if (neighbors->data->isGoal())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;

                            cout << endl
                                << "You won the game!" << endl;
                            cout << endl
                                << "Game Statistics: " << endl;
                            cout << endl
                                << "Points: " << point;
                            cout << endl
                                << "Coins: " << coins;
                            cout << endl
                                << "Trophies: " << trophies << endl;

                            cout << endl
                                << "Coins List: " << endl;
                            Node<Coin>* coin_traverse = coinsList.getHead();
                            while (coin_traverse != nullptr)
                            {
                                cout << coin_traverse->data.getValue() << " ";
                                coin_traverse = coin_traverse->next;
                            }
                            cout << endl
                                << "Trophies List: " << endl;
                            Node<Trophy>* trophy_traverse = trophiesList.getHead();
                            while (trophy_traverse != nullptr)
                            {
                                cout << trophy_traverse->data.getValue() << " ";
                                trophy_traverse = trophy_traverse->next;
                            }
                            return;
                        }
                        else
                        {
                            point += 5;
                        }

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
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getX() == carNode->getX() + 1)
                    {

                        if (neighbors->data->isObstacle())
                        {
                            point -= 10;
                            obstacles.enqueue(Obstacle("Obstacle"));
                            neighbors->data->setObstacle(false);
                        }
                        else if (neighbors->data->isDebrisObstacle())
                        {
                            point -= 5;
                            obstacles.enqueue(Obstacle("Debris"));
                            neighbors->data->setDebrisObstacle(false);
                        }
                        else if (neighbors->data->isOilSpillObstacle())
                        {
                            point -= 2;
                            obstacles.enqueue(Obstacle("Oil Spill"));
                            neighbors->data->setOilSpillObstacle(false);
                        }
                        else if (neighbors->data->isCoin50())
                        {
                            point += 5;
                            coins += 50;
                            coinsList.push_back(Coin(50));
                            neighbors->data->setCoin50(false);
                        }
                        else if (neighbors->data->isCoin100())
                        {
                            point += 5;
                            coins += 100;
                            coinsList.push_back(Coin(100));
                            neighbors->data->setCoin100(false);
                        }
                        else if (neighbors->data->isCoin150())
                        {
                            point += 5;
                            coins += 150;
                            coinsList.push_back(Coin(150));
                            neighbors->data->setCoin150(false);
                        }
                        else if (neighbors->data->isTrophy())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;
                            trophiesList.push_back(Trophy(250));
                            neighbors->data->setTrophy(false);
                        }
                        else if (neighbors->data->isGoal())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;

                            cout << endl
                                << "You won the game!" << endl;
                            cout << endl
                                << "Game Statistics: " << endl;
                            cout << endl
                                << "Points: " << point;
                            cout << endl
                                << "Coins: " << coins;
                            cout << endl
                                << "Trophies: " << trophies << endl;

                            cout << endl
                                << "Coins List: " << endl;
                            Node<Coin>* coin_traverse = coinsList.getHead();
                            while (coin_traverse != nullptr)
                            {
                                cout << coin_traverse->data.getValue() << " ";
                                coin_traverse = coin_traverse->next;
                            }
                            cout << endl
                                << "Trophies List: " << endl;
                            Node<Trophy>* trophy_traverse = trophiesList.getHead();
                            while (trophy_traverse != nullptr)
                            {
                                cout << trophy_traverse->data.getValue() << " ";
                                trophy_traverse = trophy_traverse->next;
                            }
                            return;
                        }
                        else
                        {
                            point += 5;
                        }

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
                while (neighbors != nullptr)
                {
                    if (neighbors->data->getY() == carNode->getY() + 1)
                    {

                        if (neighbors->data->isObstacle())
                        {
                            point -= 10;
                            obstacles.enqueue(Obstacle("Obstacle"));
                            neighbors->data->setObstacle(false);
                        }
                        else if (neighbors->data->isDebrisObstacle())
                        {
                            point -= 5;
                            obstacles.enqueue(Obstacle("Debris"));
                            neighbors->data->setDebrisObstacle(false);
                        }
                        else if (neighbors->data->isOilSpillObstacle())
                        {
                            point -= 2;
                            obstacles.enqueue(Obstacle("Oil Spill"));
                            neighbors->data->setOilSpillObstacle(false);
                        }
                        else if (neighbors->data->isCoin50())
                        {
                            point += 5;
                            coins += 50;
                            coinsList.push_back(Coin(50));
                            neighbors->data->setCoin50(false);
                        }
                        else if (neighbors->data->isCoin100())
                        {
                            point += 5;
                            coins += 100;
                            coinsList.push_back(Coin(100));
                            neighbors->data->setCoin100(false);
                        }
                        else if (neighbors->data->isCoin150())
                        {
                            point += 5;
                            coins += 150;
                            coinsList.push_back(Coin(150));
                            neighbors->data->setCoin150(false);
                        }
                        else if (neighbors->data->isTrophy())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;
                            trophiesList.push_back(Trophy(250));
                            neighbors->data->setTrophy(false);
                        }
                        else if (neighbors->data->isGoal())
                        {
                            point += 1000;
                            coins += 250;
                            trophies++;

                            cout << endl << "You won the game!" << endl;
                            cout << endl << "Game Statistics: " << endl;
                            cout << endl << "Points: " << point;
                            cout << endl << "Coins: " << coins;
                            cout << endl << "Trophies: " << trophies << endl;
                            cout << endl << "Coins List: " << endl << endl;

                            Node<Coin>* coin_traverse = coinsList.getHead();
                            while (coin_traverse != nullptr)
                            {
                                cout << coin_traverse->data.getValue() << " ";
                                coin_traverse = coin_traverse->next;
                            }
                            cout << endl
                                << "Trophies List: " << endl;
                            Node<Trophy>* trophy_traverse = trophiesList.getHead();
                            while (trophy_traverse != nullptr)
                            {
                                cout << trophy_traverse->data.getValue() << " ";
                                trophy_traverse = trophy_traverse->next;
                            }
                            return;
                        }
                        else
                        {
                            point += 5;
                        }

                        carNode->setCar(false);
                        neighbors->data->setCar(true);
                        break;
                    }
                    neighbors = neighbors->next;
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
    

    Stack<GraphNode*> shortestpath()
    {
        GraphNode* start = getCarNode();
        GraphNode* goal = getGoalNode();
        Queue<GraphNode*> queue;
        queue.enqueue(start);
        start->setWeight(0);

        List<GraphNode*> check; // Use an object instead of a pointer

        while (!queue.isEmpty())
        {
            GraphNode* current = queue.dequeue();
            Node<GraphNode*>* neighbors = current->getNeighbors();

            while (neighbors != nullptr)
            {
                int newWeight;
                if (neighbors->data->isCoin50())
                {
                    newWeight = current->getWeight() + 4;
                }
                else if (neighbors->data->isCoin100())
                {
                    newWeight = current->getWeight() + 3;
                }
                else if (neighbors->data->isCoin150())
                {
                    newWeight = current->getWeight() + 2;
                }
                else if (neighbors->data->isTrophy())
                {
                    newWeight = current->getWeight() + 1;
                }
                else if (neighbors->data->isDebrisObstacle())
                {
                    newWeight = current->getWeight() + 15;
                }
                else if (neighbors->data->isOilSpillObstacle())
                {
                    newWeight = current->getWeight() + 10;
                }
                else if (neighbors->data->isObstacle())
                {
                    newWeight = current->getWeight() + 20;
                }
                else
                {
                    newWeight = current->getWeight() + 5;
                }
                if (newWeight < neighbors->data->getWeight())
                {
                    neighbors->data->setWeight(newWeight);
                }
                if (!check.search(neighbors->data))
                {
                    queue.enqueue(neighbors->data);
                    check.push_back(neighbors->data);
                }

                neighbors = neighbors->next;
            }
        }

        // travel the car from start to goal
        Stack<GraphNode*> stack;
        GraphNode* current = goal;
        List<GraphNode*> check1;

        while (current != start)
        {
            stack.push(current);
            check1.push_back(current);
            Node<GraphNode*>* neighbors = current->getNeighbors();
            while (neighbors != nullptr)
            {
                if (neighbors->data->getWeight() < current->getWeight() && !check1.search(neighbors->data))
                {
                    current = neighbors->data;
                    break;
                }
                neighbors = neighbors->next;
            }
        }

        return stack;
    }

    void autoMode()
    {
        float point = 0;
        int coins = 0;
        int trophies = 0;
        List<Coin> coinsList;
        List<Trophy> trophiesList;
        GraphNode temp = getCarNodeObject();
        Stack<GraphNode*> stack = shortestpath();
        temp.setCar(false);
        temp.setPath(true);
        while (!stack.isEmpty())
        {
            GraphNode* current = stack.pop();
            current->setCar(true);
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
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
            displayMaze();
            current->setCar(false);
            current->setPath(true);
        }
        system("cls");
        point += 1000;
        coins += 250;
        trophies++;

        cout << endl
            << "You won the game!" << endl;
        cout << endl
            << "Game Statistics: " << endl;
        cout << endl
            << "Points: " << point;
        cout << endl
            << "Coins: " << coins;
        cout << endl
            << "Trophies: " << trophies << endl;

        cout << endl
            << "Coins List: " << endl;
        Node<Coin>* coin_traverse = coinsList.getHead();
        while (coin_traverse != nullptr)
        {
            cout << coin_traverse->data.getValue() << " ";
            coin_traverse = coin_traverse->next;
        }
        cout << endl
            << "Trophies List: " << endl;
        Node<Trophy>* trophy_traverse = trophiesList.getHead();
        while (trophy_traverse != nullptr)
        {
            cout << trophy_traverse->data.getValue() << " ";
            trophy_traverse = trophy_traverse->next;
        }
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
};