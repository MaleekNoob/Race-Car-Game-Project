#include "Graph.h"
#include <iostream>
#include <string>
#include <unistd.h>


using namespace std;

int main()
{
    cout << " _______ _______  ______       ______ _______ _______ _______" << endl;
    cout << " |       |_____| |_____/      |  ____ |_____| |  |  | |______" << endl;
    cout << " |_____  |     | |    \\_      |_____| |     | |  |  | |______" << endl;
    cout << endl << endl;

    sleep(2);

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