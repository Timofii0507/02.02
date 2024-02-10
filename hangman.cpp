#include "hangman.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

Hangman::Hangman(int max_tries) {
    this->max_tries = max_tries;
    tries = max_tries;
    won = false;
    choose_word();
}

void Hangman::choose_word() {
    ifstream file("words.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            words.push_back(line);
        }
        file.close();
        srand(time(NULL));
        int index = rand() % words.size();
        word = words[index];
        guess = string(word.size(), '*');
    }
    else {
        cout << "Failed to open the file with words." << endl;
        exit(1);
    }
}

void Hangman::check_letter(char letter) {
    letter = toupper(letter);
    letters.push_back(letter);
    bool found = false;
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == letter) {
            guess[i] = word[i];
            found = true;
        }
    }
    if (!found) {
        tries--;
    }
    if (guess == word) {
        won = true;
    }
}

void Hangman::show_stats() {
    cout << "Game Statistics:" << endl;
    cout << "Number of attempts used: " << max_tries - tries << endl;
    cout << "Number of attempts left: " << tries << endl;
    cout << "Time taken for the word: ";

    if (time_taken.count() >= 60) {
        int minutes = time_taken.count() / 60;
        int seconds = time_taken.count() % 60;
        cout << minutes << " minutes " << seconds << " seconds";
    }
    else {
        cout << time_taken.count() << " seconds";
    }

    cout << endl;

    cout << "Secret word: " << word << endl;
    cout << "Entered letters: ";
    for (char letter : letters) {
        cout << letter << " ";
    }
    cout << endl;
}

void Hangman::start() {
    cout << "Welcome to the \"Guess the Word\" game!" << endl;
    cout << "Your task is to guess the word I have chosen." << endl;
    cout << "You have " << max_tries << " attempts." << endl;
    cout << "Let's start!" << endl;

    auto start_time = chrono::high_resolution_clock::now();

    while (tries > 0 && !won) {
        cout << "Word: ";
        for (char letter : word) {
            if (find(letters.begin(), letters.end(), letter) != letters.end()) {
                cout << letter << " ";
            }
            else {
                cout << "* ";
            }
        }
        cout << endl;

        cout << "Attempts left: " << tries << endl;
        cout << "Enter a letter: ";
        char letter;
        cin >> letter;
        check_letter(letter);
    }

    auto end_time = chrono::high_resolution_clock::now();
    time_taken = chrono::duration_cast<chrono::seconds>(end_time - start_time);

    if (won) {
        cout << "Congratulations, you won!" << endl;
    }
    else {
        cout << "Unfortunately, you lost." << endl;
    }

    show_stats();
}
