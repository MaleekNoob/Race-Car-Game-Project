#include "List.h"

class Heap {
private:
    int* heapArray;
    int maxSize;
    int currentSize;

public:
    Heap() {
        maxSize = 50;
        currentSize = 0;
        heapArray = new int[maxSize];
    }

    ~Heap() {
        delete[] heapArray;
    }

    void insert(int value) {
        if (currentSize == maxSize) {
            cout << "Heap is full. Cannot insert more elements." << endl;
            return;
        }

        heapArray[currentSize] = value;
        int index = currentSize;
        int parentIndex = (index - 1) / 2;

        while (index > 0 && heapArray[index] > heapArray[parentIndex]) {
            swap(heapArray[index], heapArray[parentIndex]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }

        currentSize++;
    }

    int remove() {
        if (currentSize == 0) {
            cout << "Heap is empty. Cannot remove elements." << endl;
            return -1;
        }

        int root = heapArray[0];
        heapArray[0] = heapArray[currentSize - 1];
        currentSize--;

        int index = 0;
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;

        while (leftChildIndex < currentSize) {
            int maxIndex = leftChildIndex;

            if (rightChildIndex < currentSize && heapArray[rightChildIndex] > heapArray[leftChildIndex]) {
                maxIndex = rightChildIndex;
            }

            if (heapArray[index] >= heapArray[maxIndex]) {
                break;
            }

            swap(heapArray[index], heapArray[maxIndex]);
            index = maxIndex;
            leftChildIndex = 2 * index + 1;
            rightChildIndex = 2 * index + 2;
        }

        return root;
    }

    void display() {
        if (currentSize == 0) {
            cout << "Heap is empty." << endl;
            return;
        }

        cout << "Heap elements: ";
        for (int i = 0; i < currentSize; i++) {
            cout << heapArray[i] << endl;
        }
        cout << endl;
    }

    void insertInFile(fstream& file) {
        if (currentSize == 0) {
            cout << "Heap is empty. Cannot insert elements in file." << endl;
            return;
        }

        for (int i = 0; i < currentSize; i++) {
            file << heapArray[i] << endl;
        }
    }
};
