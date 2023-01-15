//Pierre Visconti
//CSCI 262
//Project 2

#include <iostream>
#include <algorithm>
#include "TicTacToe.h"

TicTacToe::TicTacToe() {

}

/***************
PUBLIC FUNCTIONS
***************/

void TicTacToe::generateBoards() {
    //Calls the recursive function that generates all boards
    _move(9, 'X');
    //Adds empty board
    _allBoards.push_back("         ");
    //Sorts all boards using the sort() function
    _sortBoards();
    //Deletes duplicate boards using the unique() function
    _deleteDuplicates();
    _calculateWins();
    _deleteTwoWins();
    cout << "total boards: " << _allBoards.size() << ", ";
    cout << "wins for 'O': " << _winsO << ", ";
    cout << "wins for 'X': " << _winsX << ", ";
    cout << "ties: " << _ties << endl;
}

int TicTacToe::writeToFile() {
    //cout << "file" << endl;
    ofstream file;
    file.open("boards.txt");
    if (file.is_open()) {
        for (int i = 0; i < _allBoards.size(); i++) {
            file << _allBoards.at(i) << endl;
        }
    } else {
        cerr << "File filed to open" << endl;
        return -1;
    }
}

/****************
PRIVATE FUNCTIONS
****************/

//Recursive function that generates all the boards
void TicTacToe::_move(int freeSpaces, char currentPlayer) {
    char nextPlayer = 'O';
    if (currentPlayer == 'O') {
        nextPlayer = 'X';
    }
    if (freeSpaces != 0) {
        for (int i = 0; i < _board.size(); i++) {
            if (_board.at(i) == ' ') {
                if (currentPlayer == 'X')
                    _board.at(i) = 'X';
                else if (currentPlayer == 'O')
                    _board.at(i) = 'O';
                _addBoard();
                _move(freeSpaces - 1, nextPlayer);
                _board.at(i) = ' ';
            }
        }
    } else {
        return;
    }
}

//Appends all elements of board to a string and then adds the string to _allBoards vector
void TicTacToe::_addBoard() {
    string currentBoard = "";
    for(int i = 0; i < _board.size(); i++) {
        if (_board.at(i) == 'X')
            currentBoard.append("X");
        else if (_board.at(i) == 'O')
            currentBoard.append("O");
        else if (_board.at(i) == ' ')
            currentBoard.append(" ");
        //_board.at(i) = ' ';
    }
    _allBoards.push_back(currentBoard);
    //cout << currentBoard << endl;
}

//Uses the sort() function from the algorithm library to sort all boards
void TicTacToe::_sortBoards() {
    sort(_allBoards.begin(), _allBoards.end());
}

//Uses the unique() function from the algorithm library to delete duplicate boards
void TicTacToe::_deleteDuplicates() {
    _allBoards.erase(unique(_allBoards.begin(), _allBoards.end()), _allBoards.end());
}

//Calculates number of wins for X and O player, and number of ties
void TicTacToe::_calculateWins() {
    _winsX = 0;
    _winsO = 0;
    _ties = 0;
    for (int i = 0; i < _allBoards.size(); i++) {
        //If three X's and not three O's, add one to winsX
        if (_isThreeInARow(i, 'X') && !_isThreeInARow(i, 'O'))
            _winsX++;
        //If three O's and not three X's, add one to winsO
        else if (_isThreeInARow(i, 'O') && !_isThreeInARow(i, 'X'))
            _winsO++;
        else if (_isThreeInARow(i, 'X') && _isThreeInARow(i , 'O'))
            _index.push_back(i);
            // _allBoards.erase(_allBoards.begin() + i);
        else
            _ties++;
    }
}

void TicTacToe::_deleteTwoWins() {
    for (int i = 0; i < _index.size(); i++) {
        _allBoards.erase(_allBoards.begin() + _index.at(i));
    }
}

//Returns true is there are three of a character in a row, column, or diagonal
bool TicTacToe::_isThreeInARow(int index, char C) {
        char zero = _allBoards.at(index).at(0);
        char one = _allBoards.at(index).at(1);
        char two = _allBoards.at(index).at(2);
        char three = _allBoards.at(index).at(3);
        char four = _allBoards.at(index).at(4);
        char five = _allBoards.at(index).at(5);
        char six = _allBoards.at(index).at(6);
        char seven = _allBoards.at(index).at(7);
        char eight = _allBoards.at(index).at(8);
        if (zero == C && four == C && eight == C)
            return true;
        else if (two == C && four == C && six == C)
            return true;
        else if (zero == C && three == C && six == C)
            return true;
        else if (one == C && four == C && seven == C)
            return true;
        else if (two == C && five == C && eight == C)
            return true;
        else if (zero == C && one == C && two == C)
            return true;
        else if (three == C && four == C && five == C)
            return true;
        else if (six == C && seven == C && eight == C)
            return true;
        else
            return false;
}
