using System;

namespace ttt_cs {
    class Program {
        static void Main(string[] args) {
            GameData tic = new GameData();
            bool playAgain = false;

            do {
                Console.WriteLine("Would you like to play again?");
                Console.WriteLine("(1) Yes");
                Console.WriteLine("(0) No");
                bool invalidChoice = false;
                
                do {
                    
                    char choice = Console.ReadKey().KeyChar;
                    switch (choice) {
                        case '1':
                            playAgain = true;
                            break;
                        case '0':
                            playAgain = false;
                            break;
                        default:
                            Console.WriteLine("Invalid input. Please enter 1 for Yes and 0 for No.");
                            invalidChoice = true;
                            break;
                    }
                } while (invalidChoice);

            } while (playAgain);
        }
    }
}