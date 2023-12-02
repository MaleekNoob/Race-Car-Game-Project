#include "List.h"

class GraphNode
{
    int x;
    int y;
    List<GraphNode*> neighbors; /* list to store GraphNode's neighbors */
    bool Car;                    /* true if car is on this Node */
    bool Goal;                   /* true if this Node is the goal */
    bool Start;                  /* true if this Node is the start */
    bool Obstacle;               /* true if this Node is an obstacle */
    bool DebrisObstacle;
    bool OilSpillObstacle;
    bool Coin50;
    bool Coin100;
    bool Coin150;
    bool Trophy;
    bool visited;
    bool path;
    int weight;
    List<GraphNode*> adjList;

public:
    GraphNode()
    {
        x = -1;
        y = -1;
        neighbors = List<GraphNode*>();
        Car = false;
        Goal = false;
        Start = false;
        Obstacle = false;
        DebrisObstacle = false;
        OilSpillObstacle = false;
        visited = false;
        Coin50 = false;
        Coin100 = false;
        Coin150 = false;
        Trophy = false;
        weight = 10000;
        adjList = List<GraphNode*>();
        path = false;
    }

    GraphNode(int x, int y)
    {
        this->x = x;
        this->y = y;
        neighbors = List<GraphNode*>();
        Car = false;
        Goal = false;
        Start = false;
        Obstacle = false;
        DebrisObstacle = false;
        OilSpillObstacle = false;
        visited = false;
        Coin50 = false;
        Coin100 = false;
        Coin150 = false;
        Trophy = false;
        weight = 10000;
        adjList = List<GraphNode*>();
        path = false;
    }

    GraphNode(const GraphNode& other)
    {
        x = other.x;
        y = other.y;
        neighbors = List<GraphNode*>();
        const Node<GraphNode*>* current = other.neighbors.getHead();
        while (current != nullptr)
        {
            neighbors.push_back(current->data);
            current = current->next;
        }
        Car = other.Car;
        Goal = other.Goal;
        Start = other.Start;
        Obstacle = other.Obstacle;
        DebrisObstacle = other.DebrisObstacle;
        OilSpillObstacle = other.OilSpillObstacle;
        Coin50 = other.Coin50;
        Coin100 = other.Coin100;
        Coin150 = other.Coin150;
        Trophy = other.Trophy;
        visited = other.visited;
        path = other.path;
        weight = other.weight;
        adjList = List<GraphNode*>();
        const Node<GraphNode*>* current2 = other.adjList.getHead();
        while (current2 != nullptr)
        {
            adjList.push_back(current2->data);
            current2 = current2->next;
        }
    }

    void displayNeighbors()
    {
        neighbors.display();
    }

    void addNeighbor(GraphNode* node)
    {
        neighbors.push_back(node);
    }

    void removeNeighbor(GraphNode* node)
    {
        neighbors.remove(node);
    }

    void addAdj(GraphNode* node)
    {
        adjList.push_back(node);
    }
    void removeAdj(GraphNode* node)
    {
        adjList.remove(node);
    }
    void displayAdj()
    {
        adjList.display();
    }
    // getters and setters
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }

    bool isSame(int x, int y)
    {
        return this->x == x && this->y == y;
    }

    bool isObstacle()
    {
        return Obstacle;
    }

    bool isDebrisObstacle()
    {
        return DebrisObstacle;
    }

    bool isOilSpillObstacle()
    {
        return OilSpillObstacle;
    }

    void setObstacle(bool isObstacle)
    {
        Obstacle = isObstacle;
    }

    void setDebrisObstacle(bool isDebrisObstacle)
    {
        DebrisObstacle = isDebrisObstacle;
    }

    void setOilSpillObstacle(bool isOilSpillObstacle)
    {
        OilSpillObstacle = isOilSpillObstacle;
    }

    bool isCar()
    {
        return Car;
    }

    void setCar(bool isCar)
    {
        Car = isCar;
    }

    bool isGoal()
    {
        return Goal;
    }

    void setGoal(bool isGoal)
    {
        Goal = isGoal;
    }

    bool isStart()
    {
        return Start;
    }

    void setStart(bool isStart)
    {
        Start = isStart;
    }

    bool isCoin50()
    {
        return Coin50;
    }

    bool isCoin100()
    {
        return Coin100;
    }

    bool isCoin150()
    {
        return Coin150;
    }

    void setCoin50(bool isCoin50)
    {
        Coin50 = isCoin50;
    }

    void setCoin100(bool isCoin100)
    {
        Coin100 = isCoin100;
    }

    void setCoin150(bool isCoin150)
    {
        Coin150 = isCoin150;
    }

    bool isTrophy()
    {
        return Trophy;
    }

    void setTrophy(bool isTrophy)
    {
        Trophy = isTrophy;
    }

    bool isVisited()
    {
        return visited;
    }

    void setVisited(bool isVisited)
    {
        visited = isVisited;
    }

    int getWeight()
    {
        return weight;
    }

    void setWeight(int weight)
    {
        this->weight = weight;
    }

    bool isPath()
    {
        return path;
    }

    void setPath(bool isPath)
    {
        path = isPath;
    }

    Node<GraphNode*>* getNeighbors()
    {
        return neighbors.getHead();
    }

    Node<GraphNode*>* getAdj()
    {
        return adjList.getHead();
    }

    bool operator==(GraphNode& node)
    {
        return x == node.getX() && y == node.getY();
    }
};