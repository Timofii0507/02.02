#ifndef HANGMAN_H
#define HANGMAN_H

#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

enum class GameState { Playing, Won, Lost };

class Hangman {
public:
    Hangman(int max_tries = 10);
    void start();

    // Accessors (if needed)
    GameState get_game_state() const;
    int get_remaining_tries() const;
    string get_display_word() const;

private:
    void choose_word();
    void check_letter(char letter);
    void show_stats();

    vector<string> words;
    string word;
    string guess;
    int tries;
    int max_tries;
    bool won;
    vector<char> letters;
    chrono::seconds time_taken;
};

#endif
