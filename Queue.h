#include <iostream>

using namespace std;

template <class T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node() : data(NULL), next(nullptr) {}
        Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *front;
    Node *back;
    int size;

public:
    Queue() : front(nullptr), back(nullptr), size(0) {}

    ~Queue()
    {
        clear();
    }

    void enqueue(const T &value)
    {
        Node *newNode = new Node(value);
        if (front == nullptr)
        {
            front = newNode;
            back = newNode;
        }
        else
        {
            back->next = newNode;
            back = newNode;
        }
        size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw "Queue is empty!";
        }
        else
        {
            Node *temp = front;
            T value = front->data;
            front = front->next;
            delete temp;
            size--;
            return value;
        }
    }

    T &peek()
    {
        return front->data;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    int getSize()
    {
        return size;
    }

    void clear()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
};