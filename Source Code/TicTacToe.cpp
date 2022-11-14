#include "TicTacToe.h"
#include <iostream>
#include <vector>

using namespace std;

TicTacToe::TicTacToe() {
    player = X;
    winner=GameNotOver;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            board[i][j] = Blank;
}

void TicTacToe::startGame() {
    cout<<"Choose mode:\nPvP or PvAI\n";
    cin>>mode;
    if (mode=="PvP")
        PvP();
    else if (mode=="PvAI")
        PvAI();
    else
    {
        cout<<"You have not entered a valid mode, please choose again.\n\n";
        startGame();
        return;
    }

}

//The GAME part:

void TicTacToe::PvP() {
    const char *Turn;
    while (true) {
        //showcase the board after a move
        for (int i=0; i<3; i++, cout<<"\n------------\n")
            for (int j=0; j<3; j++)
                board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");


        pair<int, int> action = humanMove(board, player);

        if (result(board, action, player)!=GameNotOver) {
            showResult(result(board, action, player), board);
            break; //break while loop because the game ended
        }

        player = (player == X ? O : X); //player that moves
    }
}

bool TicTacToe::validMove(pair<int, int> action, State Board[3][3]) {
    int x = action.first;
    int y = action.second;
    if (Board[x][y]!=Blank) //Someone already moved there;
        return false;
    if (!(x>=0 && x<=2 && y>=0 && y<=2)) //move is not on board
        return false;
    return true;

}

void TicTacToe::showResult(State Result, State Board[3][3]) {
    switch (Result) {
        case O:
            cout<<"\nO wins!\n";
            break;
        case Blank: //Blank is 0 so I use it as a draw
            cout<<"\nIt's a draw!\n";
            break;
        case X:
            cout<<"\nX wins!\n";
            break;
    }
    //showcase the winning/drawing board cuz the loop will be broken and won't show it if I don't show it here
    for (int i=0; i<3; i++, cout<<"\n------------\n")
        for (int j=0; j<3; j++)
            Board[i][j]==O ? cout<<" O |" : (Board[i][j]==X ? cout<<" X |" : cout<<"   |");

    winner = Result;
}

pair<int, int> TicTacToe::humanMove(State Board[3][3], State Player) {

    const char* Turn = (Player == X ? "X" : "O"); //whose turn it is in char to cout
    cout << "\nChoose a square as "<<Turn<<":";

    int x, y;
    cin>>x>>y;
    if (validMove({x, y}, board))
    {
        Board[x][y] = Player;
        return {x, y}; //Return the move to use it in result function
    }
        //if action input is invalid reenter it until is valid
    else {
        cout << "Invalid move. Please choose another one: ";
        humanMove(Board, Player);
    }

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
    if (possibleMoves(Board).empty()) //if there are no more possible moves then it is a draw cuz the board is filled
        //and nobody has won until here
        return Blank; //blank is 0 so is used as a draw

    //if it goes till here nobody wins and it's neither a draw, so we return -2
    return GameNotOver;
}

vector<pair<int, int>> TicTacToe::possibleMoves(State Board[3][3]) { //returns all possible moves in a given State board

    vector<pair<int, int>> moves;

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (Board[i][j] == Blank)
                moves.emplace_back(i, j);

    return moves;
}

//The AI part: (ofc the result and the moves etc from above are used for the AI, but these from down here are exclusively for the AI)

void TicTacToe::PvAI() {
    char Player;
    cout<<"Choose who to play as, X or O:";
    cin>>Player;
    if (Player=='X')
        player=X, bot=O;
    else
        player=O, bot=X;

    if (Player=='X')
        playAsX();
    else if (Player=='O')
        playAsO();
    else
    {
        cout<<"You have selected an invalid player type, try again:";
        PvAI();
        return;
    }

}

void TicTacToe::AIMove(State Board[3][3], pair<int, int> action, State Bot) {
    if (validMove(action, Board))
        Board[action.first][action.second] = Bot; //put the Bot in the temporary board if the move is valid
}

void TicTacToe::BotAlgo() {
    //the bot first has no move to try out, so we call the MiniMax with an invalid move, that is noMove, with x=-1, y=-1;
    //but the bot move will be in botMove global class variable, changed when we get a better score in MiniMax
    //so at the best score the move will also change accordingly
    MiniMax(board, noMove, player); //cuz player has moved
    AIMove(board, botMove, bot);
    if (result(board, botMove, bot)!=GameNotOver)
        showResult(result(board, botMove, bot), board);
}

void TicTacToe::playAsX() {
    while (winner==GameNotOver) { //the loop will break when the winner will be decided in showResult;
        //showcase the board after bot moves //firs time it will be initial board
        for (int i=0; i<3; i++, cout<<"\n------------\n")
            for (int j=0; j<3; j++)
                board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");

        cout<<'\n';

        pair<int, int> hMove = humanMove(board, player); //first the plyer moves becuse it is X;

        for (int i=0; i<3; i++, cout<<"\n------------\n")
            for (int j=0; j<3; j++)
                board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");

        cout<<'\n';

        if (result(board, hMove, player)!=GameNotOver)
            showResult(result(board, hMove, player), board);

        if (winner!=GameNotOver)//winner has been found so we dont run the BotAlgo
            break;

        BotAlgo();
    }
}

void TicTacToe::playAsO() {
    while (winner==GameNotOver) { //the loop will break when the winner will be decided in showResult;

        //showcase the board after player moves (first time it will be initial board)
        for (int i=0; i<3; i++, cout<<"\n------------\n")
            for (int j=0; j<3; j++)
                board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");

        cout<<'\n';
        BotAlgo(); //Bot first cuz it's X
        if (winner!=GameNotOver)//winner has been found
            break;

        //showcase the board after a move
        for (int i=0; i<3; i++, cout<<"\n------------\n")
            for (int j=0; j<3; j++)
                board[i][j]==O ? cout<<" O |" : (board[i][j]==X ? cout<<" X |" : cout<<"   |");
        cout<<'\n';

        pair<int, int> hMove = humanMove(board, player);
        if (result(board, hMove, player)!=GameNotOver)
            showResult(result(board, hMove, player), board);
    }
}

int TicTacToe::MiniMax(State Board[3][3], pair<int, int> action, State whoMoved) {
    //the problem is that I do call minimax with the same baord I added the move to here in the for
    //after that is done I will add another move.. but the previous move will still be in there
    //because I call the next MiniMax with this tempboard in which I add the move
    //so what I need to do is NOT ADD the move in the Board that is the argument for the function
    //because that will lead to me adding a lot of moves in the same Board
    //but I will add it in the tempBoard FROM THAT CURRENT CALL
    //that way, if I say I have a Board as argument and a move to add to it
    //I first create a tempBoard in each call in which I will add each move
    //and then it will just go like that recursive for all of the calls
    //with each new board for a new move

    //TL;DR : I add the movein the tempboard so that I don't add all the moves in the Board from the function argument
    //        because then I will have made a lot of moves nonsense;


    State tempBoard[3][3];
    //board to pass as argument to recursive MiniMax when checking different move variations.
    //in the first recursive call, the pair action will be invalid, cuz I check the board first, not make any moves;

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            tempBoard[i][j] = Board[i][j];

    if (action!=noMove)
        tempBoard[action.first][action.second] = whoMoved;
    if (result(tempBoard, action, whoMoved)!=GameNotOver) //if the game has finished return the result
        return int(result(tempBoard, action, whoMoved)); //-1 if O, 1 if X, 0 if draw


    vector<pair<int ,int>> tempMoves = possibleMoves(tempBoard);
    //the recursive MiniMax algorithm will check all the moves and the moves in their resulted board configurations
    //until a state of 1/0/-1 is reached, then if it's X we take the MAX cuz X wins on 1, if it's O we take the MIN cuz O wins on -1

    if (whoMoved == O) { //O, that is, the player, has moved, so we move with X and ofc get the max value of the X values
        int score = -2e8, currentScore; //we need to reach a max score, so we start from a minimum score, and compare it with all the results
        for (auto move: tempMoves) {
            currentScore = MiniMax(tempBoard, move, State::X);
            //in the next MiniMax we move in another tempBoard that will be created, not in this one
            // because in this one will need to be all the moves chcked, and if I move in it there will be multiple moves made
            score = max(score, currentScore);
            //if X moves then we take the maximul of all the X variations that are to come in the worst case scenario

            if (score==currentScore) //if score is the currentScore it means it has changed so we modify the bot move
            {
                //we modify the botMove variable ONLY when iterating through the first call moves of the bot
                //that means, if i am in a recursive call then I already had gone down one or more moves
                //so we won't make that move, I need to make the first move, not the one I check for down the tree
                //To check if I am in the first call I just check if the action argument is noMove , that is an invalid move
                //that's my move in the first call.
                if (action == noMove)
                    botMove = move; //then the botMove will be changed to the current move checked in the possible moves for;
            }
        }
        return score;
    }
    else { //it's O's turn cuz X has moved
        int score = 2e8, currentScore;
        for (auto move: tempMoves) {
            currentScore = MiniMax(tempBoard, move, State::O);
            score = min(score, currentScore);
            //It's O turn, we move O and take the minimum value that way O has the most advantage

            if (score==currentScore)
            {
                if (action==noMove)
                    botMove = move;
            }
        }
        return score;
    }
}

