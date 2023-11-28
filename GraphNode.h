#include <iostream>
#include <string>

using namespace std;

class Node
{
private:
    int x;
    int y;
    Node* next;
public:
    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
        next = NULL;
    }

    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    Node* getNext()
    {
        return next;
    
    }
    
    void setNext(Node* next)
    {
        this->next = next;
    }

    ~Node()
    {
        delete next;
    
    }
};


class LinkedList
{
private:
    Node* head;
    Node* tail;
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void addNode(int x, int y)
    {
        Node* temp = new Node(x, y);
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->setNext(temp);
            tail = temp;
        }
    }

    void removeNode(int x, int y)
    {
        Node* temp = head;
        Node* prev = NULL;
        while (temp != NULL)
        {
            if (temp->getX() == x && temp->getY() == y)
            {
                if (prev == NULL)
                {
                    head = temp->getNext();
                    temp->setNext(NULL);
                    delete temp;
                    return;
                }
                else
                {
                    prev->setNext(temp->getNext());
                    temp->setNext(NULL);
                    delete temp;
                    return;
                }
            }
            prev = temp;
            temp = temp->getNext();
        }
    }

    Node* getHead()
    {
        return head;
    }

    ~LinkedList()
    {
        delete head;
        delete tail;
    }
};

class GraphNode
{
private:
    int x, y;
    LinkedList* adjList;
public:
    GraphNode(int x, int y)
    {
        this->x = x;
        this->y = y;
        adjList = new LinkedList();
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    LinkedList* getAdjList()
    {
        return adjList;
    }

    void addEdge(int x, int y)
    {
        adjList->addNode(x, y);
    }

    void removeEdge(int x, int y)
    {
        adjList->removeNode(x, y);
    }

    ~GraphNode()
    {
        delete adjList;
    }
};