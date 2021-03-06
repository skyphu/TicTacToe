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
#include <iomanip>
#include <fstream>

using namespace std;
//Constants
const int ROWS = 3;
const int COLS = 3;
const int O = 0;
const int X = 1;
const int EMPTY = -1;
const string GAME_FILE = "ttt_data.txt";    //phase 5

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
void computerPlays(Game *tic);      //phase 4
int checkGameStatus(Game *tic);     //phase 5
void writeHeader(Game *tic);
void save(Game *tic);
void writeStats(Game *tic);
int saveGameStatus(Game *tic);

int main() {
  Game *tic = new Game;     //initialize a new game
  bool playAgain = false;
  tic->draws = 0;
  tic->playerWins = 0;
  tic->computerWins = 0;
  writeHeader(tic);

  do {
    play(tic);
    cout << "================================================" << endl;
    cout << "||     PLAYER       COMPUTER        DRAWS     ||" << endl;
    cout << "||" << setw(8) << tic->playerWins 
         << setw(14) << tic->computerWins 
         << setw(15) << tic->draws
         << setw(9)  << "||" << endl;
    cout << "================================================" << endl;
    cout << "Would you like to play again? " << endl;
    cout << "(1) Yes" << endl;
    cout << "(0) No" << endl;
    cin >> playAgain;
  } while(playAgain);

  cout << "Thanks for playing!" << endl;

  string gameSummary = "cat ";
  gameSummary.append(GAME_FILE);
  system(gameSummary.c_str());

  return EXIT_SUCCESS;
}

int play(Game *tic) {
  //Orchestrates the game process. Will ask for
  //the player to make a move, check whether a win or
  //draw condition has been met, then asks for the
  //computer's move.
  init(tic);            //Makes all cells empty.

  do {
    askPlayerMove(tic);   //Displays board and asks for player move.
    if (checkGameStatus(tic) == EMPTY) {
      computerPlays(tic);   //Computer chooses a move.
      checkGameStatus(tic); //Check whether someone has won or game is over. 
    } 
  } while(!tic->gameOver);

  writeStats(tic);
  return EXIT_SUCCESS;
}

void init(Game *tic) {
  //Initializes the game variables for a blank
  //grid to start a new game.

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      tic->board[row][col] = EMPTY;
    }
  }

  tic->emptyCells = ROWS * COLS;
  tic->position = 0;
  tic->gameOver = false;
  askPlayerSymbol(tic);
}

void displayRaw(Game *tic) {
  //For debugging purposes. Displays the grid
  //as it appears in the system, with Xs and Os
  //displayed as 1s and 0s respectively.

  for(int row = 0; row < ROWS; row++) {
    cout << "\t\t";
    for(int col = 0; col < COLS; col++) {
      cout << tic->board[row][col] << "  ";
    }
    cout << endl;
  }
}

void display(Game *tic) {
  //Displays the game board.

  char symbol = EMPTY;

  for (int row = 0; row < ROWS; row++) {
    cout << "\t\t";
    for(int col = 0; col < COLS; col++) {
      symbol = convertToSymbol(tic->board[row][col]);
      cout << symbol << "  ";
    }
    cout << endl;
  }
  save(tic);
}

char convertToSymbol(int val) {
  //Converts values to characters for display.
  
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
  
  bool userWantsX = true;

  cout << "Do you want X?" << endl;
  cout << "(1) Yes" << endl;
  cout << "(0) No" << endl;
  cin >> userWantsX;

  if(userWantsX) {
    tic->playerSymbol = X;
    tic->computerSymbol = O;
  } else {
    tic->playerSymbol = O;
    tic->computerSymbol = X;
  }
}

void askPlayerMove(Game *tic) {
  //Asks for the player to decide on a move on their turn.
  
  bool moveCompleted = false;
  tic->turn = tic->playerSymbol;     //Assigns turn to player
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

    tic->position = (int) pos - 48;
    moveCompleted = playOn(tic);

  } while(!moveCompleted && !tic->emptyCells);
}

void showPlayMap() {
  //Displays the grid for each valid input's location.

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
  if(!tic->emptyCells) {
    tic->gameOver = true;
    cout << "All cells are full." << endl;
    return true;
  }

  switch(tic->position) {
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

  if (tic->board[row][col] == EMPTY) {
    tic->board[row][col] = tic->turn;
    tic->emptyCells--;
    return true;
  }
  return false;
}

int someoneWins(Game *tic) {
  //Checks that win conditions are fulfilled for
  //either player.

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

void computerPlays(Game *tic) {
  //Logic for the computer's moves. At this time,
  //the computer will simply place its moves on the
  //space next to the player's move.

  bool playCompleted = false;
  tic->turn = tic->computerSymbol;

  do {
    if (tic->position == 9) {
      tic->position = 1;
    } else {
      tic->position++;
    }

    playCompleted = playOn(tic);
  } while (!playCompleted && !tic->emptyCells);
}

int checkGameStatus(Game *tic) {
  //Checks whether either player or computer has
  //met a win condition, or whether there has been a
  //draw.

  tic->winner = someoneWins(tic);

  if(tic->winner == tic->playerSymbol) {
    display(tic);
    cout << "Congratulations, you've won!!" << endl;
    tic->playerWins++;
    saveGameStatus(tic);
    return EXIT_SUCCESS;
  } else if(tic->winner == tic->computerSymbol) {
    display(tic);
    cout << "You lose..." << endl;
    tic->computerWins++;
    saveGameStatus(tic);
    return EXIT_SUCCESS;
  } else if(!tic->emptyCells) {
    display(tic);
    cout << "It's a draw!!" << endl;
    tic->draws++;
    saveGameStatus(tic);
    return EXIT_SUCCESS;
  }
  return EMPTY;
}

void writeHeader(Game *tic) {
  //Writes the game file header.

  ofstream outputFile;
  outputFile.open(GAME_FILE);

  if(!outputFile) {
    cout << "Error: File [" << GAME_FILE << "] could not be opened." << endl;
    return;
  }

  outputFile << "WELCOME TO TIC-TAC-TOE" << endl << endl
             << "Instructions: Select a cell every turn." << endl
             << "The objective is to connect three symbols" << endl
             << "in a line to win. The first to achieve this" << endl
             << "is the winner!" << endl
             << "==============================================" << endl << endl;

  outputFile.close();
  writeStats(tic);
}

void writeStats(Game *tic) {
  //Writes the game stats into a file.

  ofstream outputFile;
  outputFile.open(GAME_FILE, ios::app);

  if(!outputFile) {
    cout << "Error: File [" << GAME_FILE << "] could not be opened." << endl;
    return;
  }

  outputFile << "GAME STATS" << endl << endl
             << "PLAYER WINS: " << tic->playerWins << endl
             << "COMPUTER WINS: " << tic->computerWins << endl
             << "DRAWS: " << tic->draws << endl
             << "==============================================" << endl << endl;

  outputFile.close();
}

void save(Game *tic) {
  //Saves the game into a file.

  ofstream outputFile;
  outputFile.open(GAME_FILE, ios::app);

  if (!outputFile) {
    cout << "Error: File [" << GAME_FILE << "] could not be opened." << endl;
    return;
  }

  char symbol = EMPTY;

  for(int row = 0; row < ROWS; row++) {
    outputFile << "\t\t";
    for(int col = 0; col < COLS; col++) {
      symbol = convertToSymbol(tic-> board[row][col]);
      outputFile << symbol << "  ";
    }
    outputFile << endl;
  }
  outputFile << endl << endl;
  outputFile.close();
  
}

int saveGameStatus(Game *tic) {
  //Saves the game's results into the file.
  
  ofstream outputFile;
  outputFile.open(GAME_FILE, ios::app);

  if(!outputFile) {
    cout << "Error: File [" << GAME_FILE << "] could not be opened." << endl;
    return EXIT_FAILURE;
  }

  if(tic->winner == tic->playerSymbol) {
    outputFile << "Congratulations! You win!" << endl;
    return EXIT_SUCCESS;
  } else if(tic->winner == tic->computerSymbol) {
    outputFile << "You lose!" << endl;
    return EXIT_SUCCESS;
  } else if(!tic->emptyCells) {
    outputFile << "It's a draw!" << endl;
    return EXIT_SUCCESS;
  }

  outputFile << endl;
  outputFile.close();
  return EXIT_SUCCESS;
}