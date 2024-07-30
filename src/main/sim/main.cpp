#include <iostream>
#include "app/piece.h"
#include "app/board.h"
#include "app/actor.h"

int main(int argc, char* argv[]){
    // auto piece = Piece(PIECE_PAWN, Location(1,2));
    // print_piece(piece);

    auto board = Board();
    print_board(board);
    std::cout << std::endl;

    move_piece(&board, Location(6, 0), Location(4, 0));
    move_piece(&board, Location(7, 0), Location(5, 0));
    move_piece(&board, Location(6, 4), Location(4, 4));
    
    move_piece(&board, Location(7, 4), Location(1, 7));
    move_piece(&board, Location(1, 7), Location(5, 7));

    print_board(board);

    return 0;
}
