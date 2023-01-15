/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Pierre Visconti

    last modified: 3/7/2019
*/

#include "hangman.h"

using namespace std;

// constructor
hangman::hangman() {
    ifstream file;
    file.open("dictionary.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            string word;
            file >> word;
            int length = word.length();
            if (dic.count(length) == 0) {
                vector <string> vect;
                dic.emplace(length, vect);  //Creates new key with value vect
                dic.at(length).push_back(word); //Pushes back word to vect
            } else if (dic.count(length) == 1) {
                dic.at(length).push_back(word);
            }
        }
    } else
        cerr << "file failed to open" << endl;
}

// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int wordLength) {
    _guessesRemaining = num_guesses;
    _wordLength = wordLength;
    for (int i = 0; i < wordLength; i++) {
        _word = _word + "-";
    }
}

// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    familyVect.erase(familyVect.begin(), familyVect.end());
    _guesses.push_back(c);
    for (int i = 0; i < dic.at(_wordLength).size(); i++) {
        family f;
        f.position = get_position(dic.at(_wordLength).at(i), c);
        bool exists = false;
        for (int j = 0; j < familyVect.size(); j++) {
            if (familyVect.at(j).position == f.position)
                exists = true;
        }
        if (!exists)
            familyVect.push_back(f);
    }
    for (int i = 0; i < dic.at(_wordLength).size(); i++) {
        vector<int> position = get_position(dic.at(_wordLength).at(i), c);
        for (int j = 0; j < familyVect.size(); j++) {
            if (familyVect.at(j).position == position)
                familyVect.at(j).words.push_back(dic.at(_wordLength).at(i));
        }
    }
    int largest = familyVect.at(0).words.size();
    int index = 0;
    for (int i = 1; i < familyVect.size(); i++) {
        if (familyVect.at(i).words.size() > largest) {
            largest = familyVect.at(i).words.size();
            index = i;
        }
    }
    bool ret;
    cout << "Words in largest family: " << largest << endl;
    vector <int> zero;
    for (int i = 0; i < familyVect.at(index).position.size(); i++) {
        cout << familyVect.at(index).position.at(i) << " ";
    }
    cout << endl;
    if (familyVect.at(index).position == zero) {
        _guessesRemaining--;
        ret = false;
    } else {
        for (int i = 0; i < familyVect.at(index).position.size(); i++) {
            _word.at(familyVect.at(index).position.at(i)) = c;
        }
        ret = true;
    }
    _hiddenWord = familyVect.at(index).words.at(0);
    dic.erase(dic.begin(), dic.end());
    for (int i = 0; i < largest; i++) {
        string word = familyVect.at(index).words.at(i);
        int length = word.length();
        if (dic.count(length) == 0) {
            vector <string> vect;
            dic.emplace(length, vect);  //Creates new key with value vect
            dic.at(length).push_back(word); //Pushes back word to vect
        } else if (dic.count(length) == 1) {
            dic.at(length).push_back(word);
        }
    }
    return ret;

}

// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return _word;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return _guessesRemaining;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    sort(_guesses.begin(), _guesses.end());
    string s = "";
    for (int i = 0; i < _guesses.size(); i++) {
        s = s + _guesses.at(i);
    }
    return s;

}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for (int i = 0; i < _guesses.size(); i++) {
        if (_guesses.at(i) == c) {
            return true;
        }
    }
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    if (_word.find("-") == false) {
        return false;
    }
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    return _guessesRemaining <= 0;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    return _hiddenWord;
}

vector<int> hangman::get_position(string s, char c) {
    vector<int> vect;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == c) {
            vect.push_back(i);
        }
    }
    return vect;
}

