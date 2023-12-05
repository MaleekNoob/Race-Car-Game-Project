#pragma once
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

// ANSI escape codes for text colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void logo()
{
    cout << endl
        << endl;
    string line1 = " _______ _______  ______       ______ _______ _______ _______";
    string line2 = " |       |_____| |_____/      |  ____ |_____| |  |  | |______";
    string line3 = " |_____  |     | |    \\_      |_____| |     | |  |  | |______";
    cout << line1 << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << line2 << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << line3 << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << endl
        << endl;
}

void menu()
{
    cout << "\nMenu" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl;
}

void modes()
{
    cout << "Modes" << endl;
    cout << "1. Manual Mode" << endl;
    cout << "2. Automatic Mode" << endl;
    cout << "3. Leaderboard" << endl;
    cout << "4. Return" << endl;
}

void instructions()
{
    cout << "Instructions" << endl;
    cout << "Start: " << GREEN << " S " << RESET << endl;
    cout << "Goal: " << GREEN << " G " << RESET << endl;
    cout << "Path: " << CYAN << " P " << RESET << endl;
    cout << "Obstacle: " << RED << " O " << RESET << endl;
    cout << "DebrisObstacle: " << RED << " D " << RESET << endl;
    cout << "Oil Spill: " << RED << " OS" << RESET << endl;
    cout << "Coin 50: " << YELLOW << "50" << RESET << endl;
    cout << "Coin 100: " << YELLOW << "100" << RESET << endl;
    cout << "Coin 150: " << YELLOW << "150" << RESET << endl;
    cout << "Car: " << BLUE << " C " << RESET << endl;
    cout << "Trophy: " << MAGENTA << " T " << RESET << endl;
    cout << "Turn: +" << endl;
    cout << "Path: - OR |" << endl;;
    cout << "Up: Arrow Key Up" << endl;
    cout << "Down: Arrow Key Down" << endl;
    cout << "Left: Arrow Key Left" << endl;
    cout << "Right: Arrow Key Right" << endl;
    cout << "Press E to exit!" << endl;
}