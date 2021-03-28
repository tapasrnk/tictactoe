#include <bits/stdc++.h>
using namespace std;

struct Move
{
    int row, col;
};

char player = 'X', opponent = 'O';

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == player)
                return +10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == player)
                return +10;

            else if (b[0][col] == opponent)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == player)
            return +10;
        else if (b[0][0] == opponent)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == player)
            return +10;
        else if (b[0][2] == opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(board) == false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == '_')
                {
                    // Make the move
                    board[i][j] = player;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = max(best,
                               minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == '_')
                {
                    // Make the move
                    board[i][j] = opponent;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                               minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// This will return the best possible move for the player
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (board[i][j] == '_')
            {
                // Make the move
                board[i][j] = player;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = '_';

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main(){
    cout<<"Welcome to Tic Tac To\n";
    cout<<"Your Name\n";
    string name;
    cin >> name;
    cout<<"Enter password of 4 digit\n";
    string str;
    cin >> str;
    if(str!="****"){
        cout<<"Wrong\n";
        return 0;
    }
    cout<<"Instruction:\n";
    cout<<"Board will be like this\n";
    char arr[3][3];
    int ass=1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            arr[i][j]='_';
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }

    int no=1;
    cout<<"You can enter 1 to 9 to acess the cell\n";
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout<<no<<" ";
            no++;
        }
        cout<<"\n";
    }

    for(int l=0; l<9; l++){
        if(l%2==0){
            cout<<"Computer's Turn\n";
            Move bestMove = findBestMove(arr);
            arr[bestMove.row][bestMove.col] = 'X';
            // cout<<"X\n";
            // int x,y,no;
            // cin >> no;
            // x=ceil((double)no/3.0);
            // y=no%3;
            // if(y==0)y=3;
            // arr[x-1][y-1]='X';
        }
        else{
            cout << "Your Turn\n";
            int x, y, no;
            cin >> no;
            x = ceil((double)no / 3.0);
            y = no % 3;
            if (y == 0)
                y = 3;
            arr[x - 1][y - 1] = 'O';
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<"\n";
        }
        if(arr[0][0]=='O'&&arr[0][1]=='O'&&arr[0][2]=='O'){
            cout<<"winO"<<"\n"
                <<"Thank You\n";
                return 0;
        }
        for(int i=0; i<3; i++){
            if (arr[i][0] == 'O' && arr[i][1] == 'O' && arr[i][2] == 'O'){
                cout << "winO"
                     << "\n"
                     << "Thank You\n";
                return 0;
            }
            if (arr[i][0] == 'X' && arr[i][1] == 'X' && arr[i][2] == 'X'){
                cout << "Computer won"
                     << "\n"
                     << "Thank You\n";
                return 0;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (arr[0][i] == 'O' && arr[1][i] == 'O' && arr[2][i] == 'O')
            {
                cout << "winO\n"
                     << "Thank You\n";
                return 0;
            }
            if (arr[0][i] == 'X' && arr[1][i] == 'X' && arr[2][i] == 'X')
            {
                cout << "Computer won"
                     << "Thank You\n";
                return 0;
            }
        }

        if(arr[0][0]=='O'&&arr[1][1]=='O'&&arr[2][2]=='O'){
            cout << "winO\n"
                 << "Thank You\n";
            return 0;
        }
        if(arr[0][2]=='O'&&arr[1][1]=='O'&&arr[2][0]=='O'){
            cout << "winO\n"
                 << "Thank You\n";
            return 0;
        }

        if (arr[0][0] == 'X' && arr[1][1] == 'X' && arr[2][2] == 'X')
        {
            cout << "Computer won\n"
                 << "Thank You\n";
            return 0;
        }
        if (arr[0][2] == 'X' && arr[1][1] == 'X' && arr[2][0] == 'X')
        {
            cout << "Computer won\n"
                 << "Thank You\n";
            return 0;
        }
    }
    cout<<"Tie\n";

    return 0;
}