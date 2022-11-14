#include <iostream>
#include "TicTacToe.h"

using namespace std;

int main() {
    TicTacToe game;
    game.startGame();

    //clear buffer, wait for input to close program
    cin.clear();
    cin.get();
    cin.get();
    return 0;
}
