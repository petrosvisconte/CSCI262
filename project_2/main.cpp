//Pierre Visconti
//CSCI 262
//Project 2

#include <iostream>
#include "TicTacToe.h"
using namespace std;

int main() {
    TicTacToe t;
    //Generates all boards by calling several private functions in TicTacToe.cpp
    //Then sorts all boards and deletes duplicates
    t.generateBoards();
    //Writes all boards to file for troubleshooting purposes
    t.writeToFile();

    return 0;
}