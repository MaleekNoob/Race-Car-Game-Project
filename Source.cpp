// Sumeed_Jawad_Kanwar_22i2651
// Maleek_Hussain_Ali_22i1526

#include "Graph.h"
#include <iostream>
#include <string>
#include "Menu.h"
#include <stdlib.h>
#include <Windows.h>

using namespace std;

int main()
{
    char choice;
    do
    {
        system("cls");
        logo();
        menu();
        Maze maze;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case '1':
            char mode;
            do
            {
                system("cls");
                logo();
                modes();
                cout << "Enter your choice: ";
                cin >> mode;
                switch (mode)
                {
                case '1':
                {
                    int choice;
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

                    // Maze maze;
                    int rows, columns;
                    cout << endl
                        << "Enter the size of matrix: ";
                    cin >> rows;
                    columns = rows;
                    maze.generateMaze(rows, columns);
                    maze.manualMode();
                    Sleep(2000);
                    break;
                }
                case '2':
                {
                    int rows, columns;
                    cout << endl
                        << "Enter the size of matrix: ";
                    cin >> rows;
                    columns = rows;
                    maze.generateMaze(rows, columns);
                    bool isfirst = true;
                    while (!maze.pathExists(isfirst))
                    {
                        maze.generateMaze(rows, columns);
                        isfirst = false;
                    }
                    system("cls");
                    maze.displayMaze();
                    maze.autoMode();
                    Sleep(2000);
                    break;
                }
                case '3':
                    system("cls");
                    logo();
                    maze.LeaderBoard();
                    Sleep(1000);
                    break;
                case '4':
                    cout << "You chose to return!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
            } while (mode != '3');

            break;
        case '2':
            logo();
            instructions();
            char instructions;
            do
            {
                cin >> instructions;
                switch (instructions)
                {
                case 'E':
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
            } while (instructions != 'E');
            break;
        case '3':
            cout << "Thank You!" << endl;
            Sleep(1000);
            break;
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
            break;
        }
    } while (choice != '3');

    return 0;
}