using System;

namespace TicTacToe {
  class PlayGame {
    static void Main(string[] args) {
      GameData tic = new GameData();
      bool playAgain = false;
      
      do {
        Console.WriteLine("Would you like to play again?");
        Console.WriteLine("(1) Yes");
        Console.WriteLine("(0) No");
        
        do {
          bool invalidChoice = false;
          char choice = Console.ReadKey().KeyChar;
          switch(choice) {
            case '1':
              playAgain = true;
              break;
            case '0':
              break;
            default:
              Console.WriteLine("Invalid input.");
              invalidChoice = true;
          }
        } while(invalidChoice);
        
      } while(playAgain);
    }
  }
}