using System;
using System.Runtime.Intrinsics.X86;

namespace ttt_cs {
    public static class GameUtils {
        /* This class contains the utility functions that check
         * for valid inputs, display the game board and the play map,
         * and other miscellaneous functions that don't necessarily
         * need to be grouped with the GameData class functions.*/
        public static void Display(GameData tic) {
            var symbol = GameConstants.Empty;
            for (int row = 0; row < GameConstants.Rows; row++) {
                Console.WriteLine("\t\t");
                for (int col = 0; col < GameConstants.Cols; col++) {
                    symbol = ConvertToSymbol(tic.GetCellContents(row, col));
                    Console.Write(symbol + "  ");
                }
                Console.WriteLine("");
            }
        }

        public static char ConvertToSymbol(int val) {
            switch (val) {
                case 1:
                    return 'X';
                case 0:
                    return 'O';
                default:
                    return 'N';
            }
        }

        public static void ShowPlayMap() {
            int pos = 1;
            for (int row = 0; row < GameConstants.Rows; row++) {
                Console.WriteLine("\t\t");
                for (int col = 0; col < GameConstants.Cols; col++) {
                    Console.Write(pos++ + "  ");
                }

                Console.WriteLine("");
            }
        }

        public static bool IsPositionValid(char pos) {
            int num_ascii = (int) pos;
            if (num_ascii < 47 || num_ascii > 57) {
                return false;
            }

            return true;
        }
    }
}