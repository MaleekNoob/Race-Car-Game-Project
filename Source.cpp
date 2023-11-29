#include "Graph.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>


using namespace std;

int main()
{

    char choice;
    do
    {
        logo();
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "You chose to play the game!" << endl;

            char mode;
            do
            {
                modes();
                cout << "Enter your choice: ";
                cin >> mode;
                switch (mode)
                {
                case '1':
                    cout << "You chose to play the manual mode!" << endl;
                    
                    Maze maze;
                    int rows, columns;
                    cout << endl << "Enter the number of rows: ";
                    cin >> rows;
                    cout << "Enter the number of columns: ";
                    cin >> columns;
                    maze.generateMaze(rows, columns);
                    maze.displayMaze();

                    break;
                case '2':
                    cout << "You chose to play the automatic mode!" << endl;
                    break;
                case '3':
                    cout << "You chose to return!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
            } while (mode != '3');

            break;
        case '2':
            cout << "You chose to see the instructions!" << endl;
            break; 
        case '3':
            cout << "You chose to exit the game!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != '3');

    return 0;
}