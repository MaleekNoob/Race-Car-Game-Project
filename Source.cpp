// Sumeed_Jawad_Kanwar_22i2651
// Maleek_Hussain_Ali_22i1526

#include "Graph.h" // Include necessary header files for Graph and Menu
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
        system("cls"); // Clear the console screen
        logo();        // Display the logo
        menu();        // Display the main menu
        Maze maze;     // Create an instance of the Maze class
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case '1':
            char mode;
            do
            {
                system("cls"); // Clear the console screen
                logo();        // Display the logo
                modes();       // Display the maze modes menu
                cout << "Enter your choice: ";
                cin >> mode;
                switch (mode)
                {
                case '1':
                {
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
                {
                    system("cls");
                    logo();
                    maze.LeaderBoard();
                    Sleep(1000);
                    break;
                }
                case '4':
                {
                    cout << "You chose to return!" << endl;
                    break;
                }
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
            } while (mode != '3');

            break;
        case '2':
            logo();
            instructions(); // Display the instructions menu
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
