
#include "app/piece.h"
#include "utils/codes.h"

#define BOARD_ROW_COUNT 8
#define BOARD_COL_COUNT 8

class Board{
    public:
        Board();
        Piece get_piece(int row, int col);
        ReturnCode_e replace_piece(int row, int col, PieceName_e name, PieceColor_e color);

    private:
        Piece board_[BOARD_COL_COUNT][BOARD_ROW_COUNT];
};


void print_board(Board board);