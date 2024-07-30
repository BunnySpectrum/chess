#pragma once

#include "app/piece.h"
#include "utils/codes.h"

#define BOARD_ROW_COUNT 8
#define BOARD_COL_COUNT 8

class Board{
    public:
        Board();
        Piece get_piece(Location loc);
        ReturnCode_e set_piece(Location loc, Piece piece);

    private:
        Piece board_[BOARD_COL_COUNT][BOARD_ROW_COUNT];
};


void print_board(Board board);