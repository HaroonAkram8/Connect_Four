#include <iostream>
#include <stdbool.h>

// Constants
#define BOARD_LEN_X 7
#define BOARD_LEN_Y 6
const char EMPTY = 'E';
const char P1 = 'Y';
const char P2 = 'R';

// Globals
int numPlaced = 0;
char winner = EMPTY;
bool activeGame = false;

//Functions
void setupBoard(char (&board)[BOARD_LEN_X][BOARD_LEN_Y]);
void printBoard(char (&board)[BOARD_LEN_X][BOARD_LEN_Y]);
bool isPlaying(char (&board)[BOARD_LEN_X][BOARD_LEN_Y]);
bool pickColumn(char &player, int &column, char (&board)[BOARD_LEN_X][BOARD_LEN_Y]);
char getWinner();

int main(void) {
    char board[BOARD_LEN_X][BOARD_LEN_Y];
    char currentTurn = P1;
    int playerNum = 1;
    
    setupBoard(board);
    printBoard(board);
    activeGame = true;

    while (isPlaying(board)) {
        int column;
        do {
            std::cout << "Player " << playerNum << ": Enter a column to place a chip (0-" << BOARD_LEN_X - 1 << "): ";
            std::cin >> column;
        } while (!pickColumn(currentTurn, column, board));

        printBoard(board);

        playerNum = playerNum == 1 ? 2 : 1;
        currentTurn = currentTurn == P1 ? P2 : P1;
    }

    if (getWinner() == '=') {
        std::cout << "GAME IS TIED!!!" << std::endl;
    }
    else if (getWinner() == P1) {
        std::cout << "PLAYER 1 WINS!!!" << std::endl;
    }
    else if (getWinner() == P2) {
        std::cout << "PLAYER 2 WINS!!!" << std::endl;
    }
    else {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}

void setupBoard(char (&board)[BOARD_LEN_X][BOARD_LEN_Y]) {
    for (int y = 0; y < BOARD_LEN_Y; y++) {
        for (int x = 0; x < BOARD_LEN_X; x++) {
            board[x][y] = EMPTY;
        }
    }
}

void printBoard(char (&board)[BOARD_LEN_X][BOARD_LEN_Y]) {
    for (int y = 0; y < BOARD_LEN_Y; y++) {
        for (int x = 0; x < BOARD_LEN_X; x++)  {
           std::cout << board[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isPlaying(char (&board)[BOARD_LEN_X][BOARD_LEN_Y]) {
    if (numPlaced >= BOARD_LEN_X * BOARD_LEN_Y) {
        return false;
    }
    
    for (int y = 0; y <= BOARD_LEN_Y - 4; y++) {
        for (int x = 0; x <= BOARD_LEN_X - 4; x++)  {
            if (board[x][y] != EMPTY) {
                bool down = board[x][y] == board[x][y + 1] && board[x][y] == board[x][y + 2] && board[x][y] == board[x][y + 3];
                bool right = board[x][y] == board[x + 1][y] && board[x][y] == board[x + 2][y] && board[x][y] == board[x + 3][y];
                bool downRightDiagonal = board[x][y] == board[x + 1][y + 1] && board[x][y] == board[x + 2][y + 2] && board[x][y] == board[x + 3][y + 3];
                
                if (down || right || downRightDiagonal) {
                    winner = board[x][y];
                    return false;
                }
            }
        }
    }

    return true;
}

bool pickColumn(char &player, int &column, char (&board)[BOARD_LEN_X][BOARD_LEN_Y]) {
    if (column < 0 || column >= BOARD_LEN_X) {
        std::cout << "Please enter a valid column." << std::endl;
        return false;
    }

    for (int i = BOARD_LEN_Y - 1; i >= 0; i--) {
        if (board[column][i] == EMPTY) {
            board[column][i] = player;
            numPlaced++;
            return true;
        }
    }

    std::cout << "This column is full." << std::endl;
    return false;
}

char getWinner() {
    if (!activeGame) {
        return '-';
    }

    if (winner == EMPTY) {
        return '=';
    }

    return winner;
}