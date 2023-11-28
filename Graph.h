#include <iostream>

using namespace std;

class Graph
{
private:
    int **adjMatrix;
    int numVertices;

public:
    Graph(int numVertices);
    void addEdge(int i, int j, int weight);
    void removeEdge(int i, int j);
    int isEdge(int i, int j);
    void toString();
    ~Graph();
};