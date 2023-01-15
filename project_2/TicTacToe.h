//Pierre Visconti
//CSCI 262
//Project 2

#ifndef PROJECT2_TICTACTOE_H
#define PROJECT2_TICTACTOE_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class TicTacToe {
    public:
        TicTacToe();
        void generateBoards();
        int writeToFile();
    private:
        void _move(int freeSpaces, char nextPlayer);
        void _addBoard();
        void _sortBoards();
        void _deleteDuplicates();
        bool _isThreeInARow(int index, char C);
        void _calculateWins();
        void _deleteTwoWins();
        vector<char> _board = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
        vector<string> _allBoards;
        int _winsX;
        int _winsO;
        int _ties;
        vector<int> _index;
};


#endif //PROJECT2_TICTACTOE_H
