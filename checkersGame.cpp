#include <iostream>
#include <cstdlib> // abs() function
using namespace std;

const int ROWS = 8;
const int COLS = 8;


void display(char board[ROWS][COLS]);
bool checkWinner(char board[ROWS][COLS], char currentPlayer);
bool validMove(char board[ROWS][COLS], int srcRow, int srcCol, int dstRow, int dstCol, char currentPlayer);
void move(char board[ROWS][COLS], int srcRow, int srcCol, int dstRow, int dstCol);

void display(char board[ROWS][COLS]) {
    cout << "Checkers Board:" << endl;
    cout << "   0 1 2 3 4 5 6 7" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "  -----------------" << endl;
        cout << i << " ";

        for (int j = 0; j < COLS; j++) {
            cout << "|" << board[i][j];
        }

        cout << "|" << endl;
    }

    cout << "  -----------------" << endl;
}

bool checkWinner(char board[ROWS][COLS], char currentPlayer) {
    char opponent = (currentPlayer == 'X') ? 'O' : 'X';
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == opponent) {
                return false;
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == currentPlayer) {
                for (int dstRow = i - 2; dstRow <= i + 2; dstRow++) {
                    for (int dstCol = j - 2; dstCol <= j + 2; dstCol++) {
                        if (validMove(board, i, j, dstRow, dstCol, currentPlayer)) {
                            return false;
                        }
                    }
                }
            }
        }
    }


    return true;
}

bool validMove(char board[ROWS][COLS], int srcRow, int srcCol, int dstRow, int dstCol, char currentPlayer) {
    if (dstRow < 0 || dstRow >= ROWS || dstCol < 0 || dstCol >= COLS) {
        return false;
    }

    if (board[dstRow][dstCol] != ' ') {
        return false;
    }

    int direction = (currentPlayer == 'X') ? -1 : 1;

    int rowDistance = abs(srcRow - dstRow);
    int colDistance = abs(srcCol - dstCol);
    if (rowDistance != colDistance) {
        return false;
    }

    if (rowDistance == 1 && colDistance == 1) {
        return true;
    } else if (rowDistance == 2 && colDistance == 2) {
        int midRow = (srcRow + dstRow) / 2;
        int midCol = (srcCol + dstCol) / 2;
        char opponentPiece = (currentPlayer == 'X') ? 'O' : 'X';
        return board[midRow][midCol] == opponentPiece;
    }
    
    

    return false;
}

void move(char board[ROWS][COLS], int srcRow, int srcCol, int dstRow, int dstCol) {
    board[dstRow][dstCol] = board[srcRow][srcCol];
    board[srcRow][srcCol] = ' ';
}

int main() {
    char board[ROWS][COLS] = {
        {' ', 'O', ' ', 'O', ' ', 'O', ' ', 'O'},
        {'O', ' ', 'O', ' ', 'O', ' ', 'O', ' '},
        {' ', 'O', ' ', 'O', ' ', 'O', ' ', 'O'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '},
        {' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
        {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '}
    };

    cout << "Welcome to the Checkers Game! Good luck!" << endl;
    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        int dstRow, dstCol, srcRow, srcCol;
        display(board);
        cout << "Player " << currentPlayer << ", it's your turn! Make a move!" << endl;
        cout << "Enter the ROW and COLUMN of the piece you want to move: ";
        cin >> srcRow >> srcCol;

        if (srcRow >= 0 && srcRow < ROWS && srcCol >= 0 && srcCol < COLS && board[srcRow][srcCol] == currentPlayer) {
            cout << "Enter the ROW and COLUMN of the destination: ";
            cin >> dstRow >> dstCol;

            if (validMove(board, srcRow, srcCol, dstRow, dstCol, currentPlayer)) {
                move(board, srcRow, srcCol, dstRow, dstCol);
                if (checkWinner(board, currentPlayer)) {
                    cout << "The winner is " << currentPlayer << ". GG !" << endl;
                    gameOver = true;
                }

                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            } else {
                cout << "INVALID MOVE" << endl;
            }
        } else {
            cout << "INVALID PIECE SELECTION" << endl;
        }
    }

    return 0;
}
