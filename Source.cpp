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

    return 0;
}



