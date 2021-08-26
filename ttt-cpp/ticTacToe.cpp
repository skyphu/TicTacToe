/*======================================================
* Author: Alexandra Rosario Hernandez
* Num. Est: Y00555400
* Title: Tic-Tac-Toe
*
* Description:
* This project consists of a tic-tac-toe game. The
* purpose of this project is to combine the knowledge
* gained in previous programming courses.
* ====================================================== */
#include <iostream>
#include <string>

//Constants
const int ROWS = 3;
const int COLS = 3;
const int O = 0;
const int X = 1;
const int EMPTY = -1;

using namespace std;
/*==================================================
* GameData is a struct that contains game data.
* It facilitates data transfer from one function to
* another.
* ================================================== */

struct GameData {
  int board[ROWS][COLS];            //phase 1
  int playerSymbol;
  int computerSymbol;
  int emptyCells;
  int playerWins;
  int computerWins;
  int draws;
  int position;
  int turn;
  bool gameOver;                    //phase 2
  int winner;                       //phase 3
};

typedef GameData Game;

//Function prototypes
void init(Game *tic);               //phase 1
void displayRaw(Game *tic);
void display(Game *tic);
char convertToSymbol(int val);
int play(Game *tic);
bool playOn(Game *tic);             //phase 2
void askPlayerMove(Game *tic);
void showPlayMap();
void askPlayerSymbol(Game *tic);
bool isPositionValid(char pos);
bool checkAndSetMove(Game *tic, int row, int col);  //own addition
int someoneWins(Game *tic);         //phase 3

int main() {
  Game *tic = new Game;
  bool playAgain = false;

  do {
    play(tic);
    cout << "Would you like to play again? " << endl;
    cout << "(1) Yes" << endl;
    cout << "(0) No" << endl;
    cin >> playAgain;
  } while(playAgain);

  cout << "Thanks for playing!" << endl;

  return EXIT_SUCCESS;
}

int play(Game *tic) {
  init(tic);            //Makes all cells empty.

  do {
    askPlayerMove(tic); //Displays board and asks for player move.
  } while(!tic->gameOver);

  return EXIT_SUCCESS;
}

void init(Game *tic) {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      tic -> board[row][col] = EMPTY;
    }
  }

  tic -> emptyCells = ROWS * COLS;
  tic -> position = 0;
  tic -> gameOver = false;
  askPlayerSymbol(tic);
}

void displayRaw(Game *tic) {
  for(int row = 0; row < ROWS; row++) {
    cout << "\t\t";
    for(int col = 0; col < COLS; col++) {
      cout << tic -> board[row][col] << "  ";
    }
    cout << endl;
  }
}

void display(Game *tic) {
  char symbol = EMPTY;

  for (int row = 0; row < ROWS; row++) {
    cout << "\t\t";
    for(int col = 0; col < COLS; col++) {
      symbol = convertToSymbol(tic -> board[row][col]);
      cout << symbol << "  ";
    }
    cout << endl;
  }
}

char convertToSymbol(int val) {
  //Converts values to characters for display.
  //Phase 1.
  switch(val) {
    case X:
      return 'X';
    case O:
      return 'O';
    case EMPTY:
      return '_';
  }
}

void askPlayerSymbol(Game *tic) {
  //Asks the player if they want to play as X. Depending on
  //the answer, it sets the player symbol as the choice and
  //the computer symbol as the opposite.
  //Phase 2.
  bool userWantsX = true;

  cout << "Do you want X?" << endl;
  cout << "(1) Yes" << endl;
  cout << "(0) No" << endl;
  cin >> userWantsX;

  if(userWantsX) {
    tic -> playerSymbol = X;
    tic -> computerSymbol = O;
  } else {
    tic -> playerSymbol = O;
    tic -> computerSymbol = X;
  }
}

void askPlayerMove(Game *tic) {
  //Asks for the player to decide on a move on their turn.
  //Phase 2.
  bool moveCompleted = false;
  tic -> turn = tic -> playerSymbol;     //Assigns turn to player
  char pos = '0';

  do {
    display(tic);   //Shows the board
    cout << endl;
    showPlayMap();
    cout << endl;
    do {
      cout << "Choose a position to play in (1 - 9):";
      cin >> pos;
      if(!isPositionValid(pos)) {
        cout << endl << "Position not valid. ";
      }
    } while(!isPositionValid(pos));

    tic -> position = (int) pos - 48;
    moveCompleted = playOn(tic);

  } while(!moveCompleted && !tic->emptyCells);
}

void showPlayMap() {
  //Displays the grid for each valid input's location.
  //Phase 2.

  int pos = 1;
  for(int row = 0; row < ROWS; row++) {
    cout << "\t\t";
    for(int col = 0; col < COLS; col++) {
      cout << pos++ << "  ";
    }
    cout << endl;
  }
}

bool isPositionValid(char pos) {
  //Input validation. If player inputs a number that
  //is not between 1 and 9, return false. Otherwise,
  //return true.
  //Phase 2.

  int num_ascii = (int) pos;
  if(num_ascii < 47 || num_ascii > 57) {
    return false;
  }
  return true;
}

bool playOn(Game *tic) {
  //Checks if plays can be made.
  //Phase 2.
  if(!tic -> emptyCells) {
    tic -> gameOver = true;
    cout << "All cells are full." << endl;
    return true;
  }

  switch(tic -> position) {
    case 1:
      return checkAndSetMove(tic, 0, 0);
    case 2:
      return checkAndSetMove(tic, 0, 1);
    case 3:
      return checkAndSetMove(tic, 0, 2);
    case 4:
      return checkAndSetMove(tic, 1, 0);
    case 5:
      return checkAndSetMove(tic, 1, 1);
    case 6:
      return checkAndSetMove(tic, 1, 2);
    case 7:
      return checkAndSetMove(tic, 2, 0);
    case 8:
      return checkAndSetMove(tic, 2, 1);
    case 9:
      return checkAndSetMove(tic, 2, 2);
    default:    //Validating for anything outside 1-9 range.
      cout << endl << "This position is not valid." << endl;
      return false;
  }
}

bool checkAndSetMove(Game *tic, int row, int col) {
  //First checks that the move can be made, 
  //and if so, sets the position to player symbol and
  //updates the number of empty cells.
  //Own addition for readability.
  if (tic -> board[row][col] == EMPTY) {
    tic -> board[row][col] = tic -> turn;
    tic -> emptyCells--;
    return true;
  }
  return false;
}

int someoneWins(Game *tic) {
  //Checks that win conditions are fulfilled for
  //either player.
  //Phase 3.

  int row = 0;
  int col = 0;

  //check rows
  for(int row = 0; row < ROWS; row++) {
    if (tic->board[row][col] == tic->board[row][col+1] &&
        tic->board[row][col] == tic->board[row][col+2]) {
      if (tic->board[row][col] != EMPTY) {
        tic->gameOver = true;
        return tic->board[row][col];
      }
    }
  }

  //check cols
  for(int col = 0; col < COLS; col++) {
    if (tic->board[row][col] == tic->board[row+1][col] &&
        tic->board[row][col] == tic->board[row+2][col]) {
      if (tic->board[row][col] != EMPTY) {
        tic->gameOver = true;
        return tic->board[row][col];
      }
    }
  }

  //check diagonals
  if (tic->board[row][col] == tic->board[row+1][col+1] &&
      tic->board[row][col] == tic->board[row+2][col+2]) {
    if (tic->board[row][col] != EMPTY) {
        tic->gameOver = true;
        return tic->board[row][col];
      }
  }

  //setup for other diagonal
  row = 2;
  col = 0;

  if (tic->board[row][col] == tic->board[row-1][col+1] &&
      tic->board[row][col] == tic->board[row-2][col+2]) {
    if (tic->board[row][col] != EMPTY) {
        tic->gameOver = true;
        return tic->board[row][col];
      }
  }

  return EMPTY;
}