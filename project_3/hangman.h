#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: Pierre Visconti

    last modified: 9/24/2017
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();
    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses, int wordLength);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();
    // Return the true hidden word.
    string get_hidden_word();

    vector<int> get_position(string s, char c);
    struct family {
        vector <int> position;
        vector <string> words;
    };
    vector<family> familyVect;
    map <int, vector<string>> dic;
private:
    string _word = "";
    string _hiddenWord = "";
    string _displayWord = "";
    int _wordLength;
    int _guessesRemaining;
    vector <char> _guesses;
};

#endif
