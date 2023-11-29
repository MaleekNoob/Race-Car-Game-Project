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

    void setBoost(bool isBoost) {
        boost = isBoost;
    }

    bool isBoost() {
        return boost;
    }

    void setBoost(bool isBoost) {
        boost = isBoost;
    }

    Node<GraphNode*>* getNeighbors()
    {
        return neighbors.getHead();
    }

    bool operator==(GraphNode& node)
    {
        return x == node.getX() && y == node.getY();
    }
};