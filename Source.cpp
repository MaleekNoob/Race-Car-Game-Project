#include "Graph.h"
#include <iostream>
#include <string>
#include <unistd.h>


using namespace std;

int main()
{
    logo();
    modes();

    // sleep(2);

    Maze maze;
    int rows, columns;
    cout << endl << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> columns;
    maze.generateMaze(rows, columns);
    maze.displayMaze();
    maze.manualMode();

    return 0;
}