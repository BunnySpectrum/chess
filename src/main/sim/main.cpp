#include <iostream>
#include <unordered_set>
#include <algorithm>

#include "app/piece.h"
#include "app/board.h"
#include "app/actor.h"

#include "app/game.h"

int main(int argc, char* argv[]){
    auto game = Game();


    game.Run();

    return 0;



    // std::unordered_set<Piece> pieces;
    // pieces.insert(Piece(PIECE_PAWN, COLOR_WHITE, Location(1,1)));
    // pieces.insert(Piece(PIECE_KING, COLOR_BLACK, Location(2,2)));

    // for(const Piece& piece : pieces){
    //     std::cout << piece << std::endl;
    // }

    // std::cout << "Moves for pawn" << std::endl;
    // std::vector<Location> moves;
    // moves = valid_moves_for_piece(&board, Location(1, 1));
    // for(const Location& loc : moves){
    //     std::cout << loc << std::endl;
    // }

    // move_piece(&board, Location(1, 0), Location(3, 0));
    // move_piece(&board, Location(0, 1), Location(4, 0));
    // print_board(board);
    // std::cout << "Moves for rook" << std::endl;
    // moves = valid_moves_for_piece(&board, Location(0, 0));
    // for(const Location& loc : moves){
    //     std::cout << loc << std::endl;
    // }
    
    // std::cout << "Moves for knight" << std::endl;
    // moves = valid_moves_for_piece(&board, Location(0, 6));
    // for(const Location& loc : moves){
    //     std::cout << loc << std::endl;
    // }

    // std::cout << "Moves for bishop" << std::endl;
    // // move_piece(&board, Location(6, 3), Location(5, 3));
    // move_piece(&board, Location(7, 2), Location(4, 2));
    // print_board(board);
    // moves = valid_moves_for_piece(&board, Location(4, 2));
    // for(const Location& loc : moves){
    //     std::cout << loc << std::endl;
    // }
    // std::cout << "End of line." << std::endl;



}
