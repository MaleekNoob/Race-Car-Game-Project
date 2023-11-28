#include <iostream>
using namespace std;

int main() {

    int choice = 0;
    cout << "Welcome to the Race Car Game!\n\n";
    cout << endl << "1. Play in manual mode\n2. Play in automatic mode\n3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Play in manual mode
    }
    else if (choice == 2) {
        // Play in automatic mode
    }
    else if (choice == 3) {
        // Exit
    }
    else {
        cout << "Invalid choice. Please try again.\n";
    }

    return 0;
}