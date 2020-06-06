#include <iostream>
using namespace std;

class TicTacToe{
private:
    char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    bool winner=false;
public:
    void Printboard(){
        //print out each row with new line in between
        cout<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
        cout<<"_________"<<endl;
        cout<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
        cout<<"_________"<<endl;
        cout<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
        cout<<" "<<endl;
    }

    void InsertPiece(int row, int col) //inserts players piece
    {
        board[row-1][col-1]='X';
    }

    bool EmptySpot(int row,int col){ // returns true if spot is empty, false if spot is taken
        if(board[row-1][col-1] == ' '){
            return true;
        }
        else return false;
    }
    
    char CheckWin() // figures out if the game has reached an end-state
    {
        char winner = '0';

        //horizontal 
        for (int i = 0; i < 3; i++) {   
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') { 
                    winner = board[i][0];    
                }  
        }
            
        //vertical
        for (int j = 0; j < 3; j++)
        {
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            {
                winner = board[0][j];
            }
        }

        //diagonal
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        {
            winner = board[0][0];
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        {
            winner = board[0][2];
        }

        //check if board is full, if so and nobody won, there must be a tie
        int openSpots = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ') openSpots ++; 
            }
        }

        if (openSpots == 0 && winner == '0') return 'T'; // return tie
        else return winner; // return X wins, O wins, or '0' for nothing happened
    }

    void ComputerMove() // calls minimax algorithm to find best possible move for computer
    {
        int bestMove = -1000; //initialize to something very negative so computer will not choose to not move
        int best_row;
        int best_col; 
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int score = minimax(false); // puts piece in and checks what score will result if both sides play optimally
                    board[i][j] = ' '; 
                    if (score > bestMove) // if the resulting score is better than the previous, this is the new best move
                    {
                        bestMove = score;
                        best_row = i;
                        best_col = j;   
                    }   
                }       
            }
        }
        board[best_row][best_col] = 'O'; //the best move will have been found, and we can put the computers piece in now
    }

    int minimax(bool isMaximizing)
    {
        char result = CheckWin(); 
        if (result != '0') // as with all recursive functions, we first check the base cases
        {                
            if (result == 'O') return 10; // computer wins
            else if (result == 'X') return - 10; // player wins
            else return 0; // tie
        }

        if (isMaximizing) // finds optimal move for computer
        {
            int bestScore = -1000;

            for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == ' ')
                        {
                            board[i][j] = 'O';
                            int score = minimax(false); // place piece here and check how the player could respond
                            board[i][j] = ' ';
                            if (score > bestScore) bestScore = score;  
                        }       
                    }
                }
            return bestScore;
        }
        else //finds optimal move for player
        {
            int bestScore = 1000;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i][j] == ' ')
                    {
                        board[i][j] = 'X';
                        int score = minimax(true); // place piece here and check how computer could respond
                        board[i][j] = ' ';
                        if (score < bestScore) bestScore = score;  
                    }       
                }
            }
            return bestScore;
        }   
    }
};

int main() {
    bool player = true; // start with players turn
    TicTacToe tictactoe; // initialize game
    tictactoe.Printboard();
    while(true) // keep game loop going until a winner or tie is declared
    { 
        int row, col;
        if(player == false)
        {
            tictactoe.ComputerMove(); 
        }
        else
        {
            bool validmove = false;
            while (!validmove) // keep asking player to input a move until they input an empty space that can be moved to
            {
                cout<<"Enter row: ";
                cin>>row;
                cout<<"Enter column: ";
                cin>>col;
                if (tictactoe.EmptySpot(row, col)) validmove = true; // if the spot is empty, the move is valid
                else cout << "That spot is taken. " << endl; // else, let player know that the move is invalid
            }
            tictactoe.InsertPiece(row,col); // inserts piece once move is valid
        }
        if (!player) tictactoe.Printboard(); // only reprint board after computer moves to avoid messy printing
        char result = tictactoe.CheckWin(); // after a move, check if there is a winner/tie
        if (result != '0')
        {
            if (result == 'X')
            {
                cout << "Player wins!" << endl;
                break; 
            }
            else if (result == 'O')
            {
                cout << "Computer wins!" << endl;
                break;
            }
            else
            {
                cout << "Tie!" << endl;
                break;
            }
        }
        player=!player; // change whose turn it is
    }
    return 0;
}