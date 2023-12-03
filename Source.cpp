#include "Graph.h"
#include <iostream>
#include <string>
// #include <unistd.h>
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
        cout << endl;
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
                {
                    int choice;
                    cout << "You chose to play the manual mode!" << endl;
                    cout << "Choose complexity: " << endl;
                    cout << "1. Easy" << endl;
                    cout << "2. Medium" << endl;
                    cout << "3. Hard" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    while (choice < 1 || choice > 3)
                    {
                        cout << "Invalid choice!" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                    }

                    char complexity;

                    switch (choice)
                    {
                    case 1:
                        complexity = 'e';
                        break;
                    case 2:
                        complexity = 'm';
                        break;
                    case 3:
                        complexity = 'h';
                        break;
                    }

                    Maze maze;
                    int rows, columns;
                    cout << endl << "Enter the size of matrix: ";
                    cin >> rows;
                    columns = rows;
                    maze.generateMaze(rows, columns);
                    maze.displayMaze();
                    maze.manualMode();

                    break;
                }
                case '2':
                {
                    cout << "You chose to play the automatic mode!" << endl;

                    Maze maze;
                    int rows, columns;
                    cout << endl << "Enter the size of matrix: ";
                    cin >> rows;
                    columns = rows;
                    maze.generateMaze(rows, columns);
                    //maze.displayMaze();
                    while (!maze.pathExists())
                    {
                        maze.generateMaze(rows, columns);
                    }
                    //system("cls");
                    cout << "Graph Generated: " << endl;
                    maze.displayMaze();
                    maze.autoMode();
                    break;
                }
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
            instructions();
            char instructions;
            do
            {
                cin >> instructions;
                switch (instructions)
                {
                case 'E':
                    cout << "You chose to exit the instructions!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
            } while (instructions != 'E');
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