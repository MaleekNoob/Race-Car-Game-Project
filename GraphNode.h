#include "List.h"

class GraphNode {
    int x;
    int y;
    List<GraphNode*> neighbors; /* list to store GraphNode's neighbors */
    bool isCar; /* true if car is on this Node */
    bool isGoal; /* true if this Node is the goal */
    bool isStart; /* true if this Node is the start */
    bool isObstacle; /* true if this Node is an obstacle */

public:
    GraphNode() {
        x = -1;
        y = -1;
        neighbors = List<GraphNode*>();
        isCar = false;
        isGoal = false;
        isStart = false;
        isObstacle = false;
    }

    GraphNode(int x, int y) {
        this->x = x;
        this->y = y;
        neighbors = List<GraphNode*>();
        isCar = false;
        isGoal = false;
        isStart = false;
        isObstacle = false;
    }

    void addNeighbor(GraphNode* node) {
        neighbors.push_back(node);
    }

    void removeNeighbor(GraphNode* node) {
        neighbors.remove(node);
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    bool isSame(int x, int y) {
        return this->x == x && this->y == y;
    }
};