#include "List.h"

class GraphNode
{
    int x;
    int y;
    List<GraphNode*> neighbors; /* list to store GraphNode's neighbors */
    bool Car; /* true if car is on this Node */
    bool Goal; /* true if this Node is the goal */
    bool Start; /* true if this Node is the start */
    bool Obstacle; /* true if this Node is an obstacle */
    bool boost;
    bool visited;
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
        visited = false;
        boost = false;
        weight = 5;
        adjList = List<GraphNode*>();
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
        visited = false;
        boost = false;
        weight = 5;
        adjList = List<GraphNode*>();
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
    //getters and setters
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

    void setObstacle(bool isObstacle)
    {
        Obstacle = isObstacle;
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

    bool isBoost() {
        return boost;
    }

    void setBoost(bool isBoost)
    {
        boost = isBoost;
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