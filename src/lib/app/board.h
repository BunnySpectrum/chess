#pragma once

#include "app/piece.h"
#include "utils/codes.h"


class Board{
    public:
        Board();
        Piece get_piece(Location loc) const;
        ReturnCode_e set_piece(Location loc, Piece piece);
        ReturnCode_e clear_piece(Location loc);
        std::vector<Location> getLocationsForColor(PieceColor_e color) const;


    private:
        Piece board_[BOARD_COL_COUNT][BOARD_ROW_COUNT];
};


void print_board(Board board);
void init_standard_board(Board* pBoard);