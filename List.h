// Sumeed_Jawad_Kanwar_22i2651
// Maleek_Hussain_Ali_22i1526

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

template <class T>
struct Node
{
    T data;
    Node *next;
    Node() : data(NULL), next(nullptr) {}
    Node(const T &value) : data(value), next(nullptr) {}
};

template <typename T>
class List
{
private:
    Node<T> *head;
    int size;

public:
    List() : head(nullptr), size(0) {}

    ~List()
    {
        clear();
    }

    void push_front(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void push_back(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node<T> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    void pop_front()
    {
        if (head == nullptr)
        {
            return;
        }
        Node<T> temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void pop_back()
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node<T> current = head;
            while (current->next->next != nullptr)
            {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size--;
    }

    T &front()
    {
        return head->data;
    }

    const T &front() const
    {
        return head->data;
    }

    T &back()
    {
        Node<T> *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        return current->data;
    }

    const T &end() const
    {
        Node<T> *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        return current->data;
    }

    int getSize() const
    {
        return size;
    }

    bool empty() const
    {
        return size == 0;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    void remove(const T &value)
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->data == value)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            size--;
        }
        else
        {
            Node<T> *current = head;
            while (current->next != nullptr && current->next->data != value)
            {
                current = current->next;
            }
            if (current->next != nullptr)
            {
                Node<T> *temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
            }
        }
    }

    Node<T> *getHead() const
    {
        return head;
    }

    // find function
    bool find(T value)
    {
        if (head == nullptr)
        {
            return false;
        }
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void display()
    {
        Node<T> *current = head;
        for (int i = 0; current != nullptr; i++)
        {
            cout << "   " << current;
            current = current->next;
        }
        return;
    }

    bool search(T value)
    {
        if (head == nullptr)
        {
            return false;
        }
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    List<T> &operator=(const List<T> &other)
    {
        if (this == &other)
        {
            return *this;
        }

        // Clear the current list
        Node<T> *current = head;
        while (current != nullptr)
        {
            Node<T> *temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        size = 0;

        // Copy elements from 'other'
        current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }

        return *this;
    }
};

void logo()
{
    cout << endl
         << endl;
    string line1 = " _______ _______  ______       ______ _______ _______ _______";
    string line2 = " |       |_____| |_____/      |  ____ |_____| |  |  | |______";
    string line3 = " |_____  |     | |    \\_      |_____| |     | |  |  | |______";
    cout << line1 << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << line2 << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << line3 << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl
         << endl;
}

void menu()
{
    cout << "\nMenu" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl;
}

void modes()
{
    cout << "Modes" << endl;
    cout << "1. Manual Mode" << endl;
    cout << "2. Automatic Mode" << endl;
    cout << "3. Leaderboard" << endl;
    cout << "4. Return" << endl;
}

void instructions()
{
    cout << "Instructions" << endl;
    cout << "Start: S" << endl;
    cout << "Goal: G" << endl;
    cout << "Obstacle: O" << endl;
    cout << "Boost: B" << endl;
    cout << "Car: C" << endl;
    cout << "Turn: +" << endl;
    cout << "Path: - / |" << endl;
    cout << "Up: W" << endl;
    cout << "Down: S" << endl;
    cout << "Left: A" << endl;
    cout << "Right: D" << endl;
    cout << "Press E to exit!" << endl;
}

#endif