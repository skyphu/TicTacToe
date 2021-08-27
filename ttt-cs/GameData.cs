using System;
using GameConstants;

namespace TicTacToe {
  class GameData {
    int board[GameConstants.ROWS][GameConstants.COLS];
    int playerSymbol;
    int computerSymbol;
    int emptyCells;
    int playerWins;
    int computerWins;
    int draws;
    int position;
    int turn;
    bool gameOver;
    int winner;
  }

  public GameData() {
    for (int row = 0; row < GameConstants.ROWS; row++) {
      for (int col = 0; col < GameConstants.COLS; col++) {
        board[row][col] = GameConstants.EMPTY;
      }
    }
    emptyCells = GameConstants.ROWS * GameConstants.COLS;
    position = 0;
    gameOver = false;
    askPlayerSymbol();
  }

  void askPlayerSymbol() {
    //Asks the player if they want to play as X. Depending on
    //the answer, it sets the player symbol as the choice and
    //the computer symbol as the opposite.
    //Phase 2.

    Console.WriteLine("Do you want X?");
    Console.WriteLine("(1) Yes");
    Console.WriteLine("(0) No");
    do {
      char choice = Console.ReadKey().KeyChar;

      switch(choice) {
        case '1': 
          playerSymbol = GameConstants.X;
          computerSymbol = GameConstants.O;
          break;
        case '2':
          playerSymbol = GameConstants.O;
          computerSymbol = GameConstants.X;
          break;
        default:
          Console.WriteLine("Invalid input.")
          choice = Console.ReadKey().KeyChar;
      }
    } while (choice != '1' || choice != '0')
  }
}