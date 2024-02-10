#include <iostream>
#include "hangman.h"
#include <Windows.h>

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Hangman game;
    game.start();
    return 0;
}
