#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <string>
using namespace std;

class TicTacToe {
public:
    int player; //1 is X's turn, -1 is O's turn
    string mode; //if player vs player or player vs bot

    enum State{Blank=0, O=-1, X=1, GameNotOver};
    State board[3][3] = {Blank};
    State winner; //1 if X wins, 0 if draw, -1 if O wins

    TicTacToe();

    void startGame();

    State result(State Board[3][3], pair<int, int> action, State Player);
    void Move(State Board[3][3], pair<int, int> action, State Player);

    vector<pair<int, int>>  possibleMoves(State Board[3][3]);
    void MiniMax(State Board[3][3], pair<int, int> action, State Player);

};

#endif //TICTACTOE_H
