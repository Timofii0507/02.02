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
        cout << "�� ������� ������� ���� � �������." << endl;
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
    cout << "���������� ���:" << endl;
    cout << "ʳ������ ������������ �����: " << max_tries - tries << endl;
    cout << "ʳ������ ��������� �����: " << tries << endl;
    cout << "���, ���������� �� �����: ";

    if (time_taken.count() >= 60) {
        int minutes = time_taken.count() / 60;
        int seconds = time_taken.count() % 60;
        cout << minutes << " ������ " << seconds << " ������";
    }
    else {
        cout << time_taken.count() << " ������";
    }

    cout << endl;

    cout << "���������� �����: " << word << endl;
    cout << "������ �����: ";
    for (char letter : letters) {
        cout << letter << " ";
    }
    cout << endl;
}

void Hangman::start() {
    cout << "³���� � �� \"������ �����\"!" << endl;
    cout << "���� �������� - ������� �����, ��� � �������." << endl;
    cout << "� ��� � " << max_tries << " �����." << endl;
    cout << "��������!" << endl;

    auto start_time = chrono::high_resolution_clock::now();

    while (tries > 0 && !won) {
        cout << "�����: ";
        for (char letter : word) {
            if (find(letters.begin(), letters.end(), letter) != letters.end()) {
                cout << letter << " ";
            }
            else {
                cout << "* ";
            }
        }
        cout << endl;

        cout << "���������� �����: " << tries << endl;
        cout << "������ �����: ";
        char letter;
        cin >> letter;
        check_letter(letter);
    }

    auto end_time = chrono::high_resolution_clock::now();
    time_taken = chrono::duration_cast<chrono::seconds>(end_time - start_time);

    if (won) {
        cout << "³����, �� �������!" << endl;
    }
    else {
        cout << "�� ����, �� ��������." << endl;
    }

    show_stats();
}
