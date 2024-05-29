#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function headers definition area
void initialMenu();
void clearScreen();
void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);
int checkBoard(char board[3][3]);
void displayInstructions();
void game(char playerOneName[], char playerTwoName[], int playerOneScore, int playerTwoScore);

void clearScreen() {
    system("cls");
}

void initializeBoard(char board[3][3]) {
    // Traverse each position of the board and set the symbol to '-'
    int row, column;
    for (row = 0; row < 3; row++) {
        for (column = 0; column < 3; column++) {
            board[row][column] = '-';
        }
    }
}

void displayBoard(char board[3][3]) {
    // Display the board with its rows and columns breaking the line after each row
    int row, column;
    printf("\n");
    for (row = 0; row < 3; row++) {
        for (column = 0; column < 3; column++) {
            printf(" %c ", board[row][column]);
            if (column < 2) {
                printf("|"); // Add vertical separator
            }
        }
        printf("\n");
        if (row < 2) {
            printf("---+---+---\n"); // Add horizontal separator between rows
        }
    }
}

// 1 = X wins, 2 = O wins, 0 = Nothing happened
int checkBoard(char board[3][3]) {
    int row, column;
    // Check rows
    for (row = 0; row < 3; row++) {
        if (board[row][0] == 'X' && board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            return 1;
        } else if (board[row][0] == 'O' && board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            return 2;
        }
    }

    // Check columns
    for (column = 0; column < 3; column++) {
        if (board[0][column] == 'X' && board[0][column] == board[1][column] && board[1][column] == board[2][column]) {
            return 1;
        } else if (board[0][column] == 'O' && board[0][column] == board[1][column] && board[1][column] == board[2][column]) {
            return 2;
        }
    }

    // Main Diagonal
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') {
            return 1;
        } else {
            return 2;
        }
    }

    // Secondary Diagonal
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') {
            return 1;
        } else {
            return 2;
        }
    }

    return 0;
}

void displayInstructions() {
    printf("\nPositions Map:");
    printf("\n 7 | 8 | 9");
    printf("\n 4 | 5 | 6");
    printf("\n 1 | 2 | 3");
}

void game(char playerOneName[], char playerTwoName[], int playerOneScore, int playerTwoScore) {
    // General Variables
    char currentPlayerName[100]; // Player names
    char board[3][3]; // Game Board
    int row, column; // Auxiliary for the board
    int playedRow, playedColumn, playedPosition; // Position where the player places their mark
    int gameState = 1; // 0 = No game, 1 = In Progress
    int playerTurn = 1; // 1 = X, 2 = O
    int round = 0; // Total rounds played
    int option; // Restart option
    int madeMove; // Check if the player made a move

    // Set '-' on the board to indicate empty
    initializeBoard(board);

    while (round < 9 && gameState == 1) {
        clearScreen();
        printf("\nRound:%d\n", round);
        printf("Score:%s %d x %d %s\n", playerOneName, playerOneScore, playerTwoScore, playerTwoName);

        // Display the board on the screen
        displayBoard(board);

        // Display which number corresponds to which position
        displayInstructions();

        // Update the name of the current player
        if (playerTurn == 1) {
            strcpy(currentPlayerName, playerOneName);
        } else {
            strcpy(currentPlayerName, playerTwoName);
        }

        madeMove = 0;

        // Matrix of possible positions
        int positions[9][2] = {{2,0},{2,1},{2,2},{1,0},{1,1},{1,2},{0,0},{0,1},{0,2}};

        while (madeMove == 0) {
            // Read the move
            printf("\n%s Enter a position according to the map above:", currentPlayerName);
            scanf("%d", &playedPosition);

            // Pass the row and column according to the position matrix displayed in the map
            playedRow = positions[playedPosition-1][0];
            playedColumn = positions[playedPosition-1][1];

            // Check if the position is empty
            if (board[playedRow][playedColumn] == '-') {
                // Managed to place a marker
                madeMove = 1;

                // Check whose turn it is to place the marker
                if (playerTurn == 1) {
                    board[playedRow][playedColumn] = 'X';
                    playerTurn = 2;
                } else {
                    board[playedRow][playedColumn] = 'O';
                    playerTurn = 1;
                }
            }
        }

        // Check if the game is over
        int result = checkBoard(board);
        if (result == 1) {
            printf("Player X wins");
            playerOneScore++;
            gameState = 0;
        } else if (result == 2) {
            printf("Player O wins");
            playerTwoScore++;
            gameState = 0;
        }

        // Increase a round
        round++;
    }

    displayBoard(board);
    printf("End of game\n");
    printf("What do you want to do?\n");
    printf("1-Continue playing\n");
    printf("2-Initial Menu\n");
    printf("3-Exit\n");
    scanf("%d", &option);
    if (option == 1) {
        game(playerOneName, playerTwoName, playerOneScore, playerTwoScore);
    } else if (option == 2) {
        initialMenu();
    }
}

void initialMenu() {
    // Option chosen by the user
    int option = 0;

    // Player names
    char playerOneName[100], playerTwoName[100];

    // While the player does not enter a valid option, show the menu again
    while (option < 1 || option > 3) {
        clearScreen();
        printf("Welcome to Tic Tac Toe\n");
        printf("1 - Play\n");
        printf("2 - About\n");
        printf("3 - Exit\n");
        printf("Choose an option and press ENTER:");

        // Read the option
        scanf("%d", &option);

        // Do something according to the chosen option
        switch (option) {
            case 1:
                // Start the game
                printf("Enter player 1's name:");
                scanf("%s", playerOneName);
                printf("Enter player 2's name:");
                scanf("%s", playerTwoName);
                game(playerOneName, playerTwoName, 0, 0);
                break;
            case 2:
                // Show game information
                printf("Game created on 29/05/2024 by Sady Neto after the course of C and C++ development\n");
                break;
            case 3:
                printf("See you later!");
                break;
        }
    }
}

int main() {
    initialMenu();
    return 0;
}

