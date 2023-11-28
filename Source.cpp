#include "Graph.h"

int main() {
    Maze maze;
    int rows, columns;
    cout << endl << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> columns;
    maze.generateMaze(rows, columns);
    maze.displayMaze();
    // int choice;
    // cout << "1. Manual Mode\n2. Automatic Mode\nEnter your choice: ";
    // cin >> choice;

    // if (choice == 1) {

    // }

    return 0;
}



