#include <iostream>
#include <string>
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
class List {
private:

    Node<T>* head;
    int size;

public:
    List() : head(nullptr), size(0) {}

    ~List() {
        clear();
    }

    void push_front(const T& value) {
        Node<T>* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node<T> temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void pop_back() {
        if (head == nullptr) {
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node<T> current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size--;
    }

    T& front() {
        return head->data;
    }

    const T& front() const {
        return head->data;
    }

    T& back() {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data;
    }

    const T& end() const {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data;
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    void remove(const T& value) {
        if (head == nullptr) {
            return;
        }
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr && current->next->data != value) {
                current = current->next;
            }
            if (current->next != nullptr) {
                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
            }
        }
    }

    Node<T>* getHead() {
        return head;
    }

    // find function
    bool find( T value) {
        if (head == nullptr) {
            return false;
        }
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void display() {
        Node<T>* current = head;
        for (int i = 0; current != nullptr; i++) {
            cout << "   " << current->data ;
            current = current->next;
        }
        return;
    }
};