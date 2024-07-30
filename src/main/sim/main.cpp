#include <iostream>
#include "app/piece.h"
#include "app/board.h"

int main(int argc, char* argv[]){
    // auto piece = Piece(PIECE_PAWN, Location(1,2));
    // print_piece(piece);

    auto board = Board();
    print_board(board);
    std::cout << std::endl;

    board.replace_piece(6, 0, PIECE_NOTHING, COLOR_WHITE);
    board.replace_piece(5, 0, PIECE_PAWN, COLOR_WHITE);
    print_board(board);

    return 0;
}
