#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <string>
using namespace std;

class TicTacToe {
public:
    string mode; //if player vs player or player vs bot

    enum State{Blank=0, O=-1, X=1, GameNotOver};

    State player; //1 is X's turn, -1 is O's turn
    State bot; //same as player

    pair<int, int> botMove;
    pair<int, int> noMove = {-1 , -1};

    State board[3][3] = {Blank};
    State winner; //X, O or Blank if draw

    TicTacToe();

    void startGame();
    void PvP();
    void PvAI();

    void playAsX();
    void playAsO();
    void BotAlgo();

    bool validMove(pair<int, int> action, State Board[3][3]);
    pair<int, int> humanMove(State Board[3][3], State Player);
    State result(State Board[3][3], pair<int, int> action, State Player);
    void showResult(State Result, State Board[3][3]);
    vector<pair<int, int>>  possibleMoves(State Board[3][3]);

    void AIMove(State Board[3][3], pair<int, int> action, State Bot);
    int MiniMax(State Board[3][3], pair<int, int> action, State whoMoved);

};

#endif //TICTACTOE_H
