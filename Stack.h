#include <iostream>

using namespace std;

template <class T>

class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node() : data(NULL), next(nullptr) {}
        Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *top;
    int size;
public:
    Stack() : top(nullptr), size(0) {}

    ~Stack()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop()
    {
        if (top == nullptr)
        {
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    T& peek()
    {
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    int getSize()
    {
        return size;
    }

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};