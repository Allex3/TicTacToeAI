#include "TicTacToe.h"
#include <iostream>
#include <vector>

using namespace std;

TicTacToe::TicTacToe() {
    player = 1;
}


//The GAME part:

void TicTacToe::startGame() {
    cout<<"Choose mode:\nPvP or PvAI\n";
    cin>>mode;
    if (mode=="PvP") {
        const char *Turn;
        State Player;
        while (true) {
            //showcase the board after a move
            for (int i=0; i<3; i++, cout<<"\n------------\n")
                for (int j=0; j<3; j++)
                    board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");

            Player = (player==-1? O : X); //player that moves

            Turn = (player == -1 ? "O" : "X"); //whose turn it is in char, same as above but above is -1 or 1
            cout << "Choose a square as "<<Turn<<":";

            pair<int, int> action;
            cin >> action.first>>action.second;
            while (!(action.first>=0 && action.second>=0 && action.first<=2 && action.second<=2))
            {
                //if action input is invalid reenter it until is valid
                cout<<"Invalid move. Please choose another one: ";
                cin >> action.first>>action.second;
            }

            Move(board, action, Player);

            if (result(board, action, Player)!=GameNotOver)
            {
                switch (result(board, action, Player)) {
                    case O:
                        cout<<"O wins!\n";
                        break;
                    case Blank: //Blank is 0 so I use it as a draw
                        cout<<"It's a draw!\n";
                        break;
                    case X:
                        cout<<"X wins!\n";
                        break;
                }
                //showcase the winning/drawing board cuz the loop will be broken and won't show it if I don't show it here
                for (int i=0; i<3; i++, cout<<"\n------------\n")
                    for (int j=0; j<3; j++)
                        board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");

                winner = Player;
                break; //break while loop cuz the game ended
            }

            player==1 ? player=-1 : player = 1; //if player is X make player O, else means player is O then make it X
        }
    }
    else if (mode=="PvAI")
    {
        return;
    }
    else
    {
        cout<<"You have not entered a valid mode, please choose again.\n\n";
        startGame();
        return;
    }

}

void TicTacToe::Move(State Board[3][3], pair<int, int> action, State Player) {
    int x = action.first;
    int y = action.second;

    Board[x][y] = Player;
}

TicTacToe::State TicTacToe::result(State Board[3][3], pair<int, int> action, State Player) {
    int x = action.first; //the row
    int y = action.second; //the column

    for (int j=0; j<3; j++) {//check the row, cuz element was added on row x
        if (Board[x][j] != Player) //if on the row checked we find a cell that doesn't have the player we break loop
            break;
        if (j == 2) //last column was reached with no lose, so it's a win
            return Player;
    }
    for (int i=0; i<3; i++) {//now same thing for the column where it was added, we check the column
        if (Board[i][y] != Player)
            break;
        if (i==2) //last row reached with no lose, so it's a win
            return Player;
    }
    if (x==y) //if x=y, player was added on the diagonal so  check them
        for (int i=0; i<3; i++) {
            if (Board[i][i] !=Player)
                break;
            if (i==2) //didn't break until last element so player must win
                return Player;
        }
    if (x+y==3-1) //check secondary diagonal, so x will be 3-1-y, as will the column when checking
        for (int i=0; i<3; i++) {
            if (Board[i][(3-1)-i] != Player)
                break;
            if (i==2) //didn't break till last row so player must win
                return Player;
        }
    if (possibleMoves(board).empty()) //if there are no more possible moves then it is a draw cuz the board is filled
        //and nobody has won until here
        return Blank; //blank is 0 so is used as a draw

    //if it goes till here nobody wins and it's neither a draw, so we return -2
    return GameNotOver;
}


//The AI part: (ofc the result and the moves etc from above are used for the AI, but these from down here are exclusively for the AI)
//(also possibleMoves is called to see if there is a draw so it is not only used by the AI :( )

vector<pair<int, int>> TicTacToe::possibleMoves(State Board[3][3]) {

    vector<pair<int, int>> moves;
    int cnt=0;

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (board[i][j] == Blank)
                moves.emplace_back(i, j);

    return moves;
}

void TicTacToe::MiniMax(State Board[3][3], pair<int, int> action, State Player) {

}

