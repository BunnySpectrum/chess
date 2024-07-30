#include "board.h"

Board::Board(){
    PieceColor_e color;
    for(int row = 0; row < BOARD_ROW_COUNT; row++){
        color = row < 4 ? COLOR_BLACK : COLOR_WHITE;
        for(int col = 0; col < BOARD_COL_COUNT; col++){
            if(row == 1 || row == 6){
                board_[col][row] = Piece(PIECE_PAWN_FIRST, color);
            }
            else if((row==0 || row==7) && (col==0 || col==7)){
                board_[col][row] = Piece(PIECE_ROOK_FIRST, color);
            }
            else if((row==0 || row==7) && (col==1 || col==6)){
                board_[col][row] = Piece(PIECE_KNIGHT, color);
            }
            else if((row==0 || row==7) && (col==2 || col==5)){
                board_[col][row] = Piece(PIECE_BISHOP, color);
            }
            else if((row==0 || row==7) && (col==3)){
                board_[col][row] = Piece(PIECE_QUEEN, color);
            }
            else if((row==0 || row==7) && (col==4)){
                board_[col][row] = Piece(PIECE_KING_FIRST, color);
            }
            else{
                board_[col][row] = Piece(PIECE_NOTHING, color);
            }
        }
    }

}
        
Piece Board::get_piece(int row, int col){
    return board_[col][row];
}

ReturnCode_e Board::replace_piece(int row, int col, PieceName_e name, PieceColor_e color){
    if(row < 0 || row >= BOARD_ROW_COUNT || col < 0 || col >= BOARD_COL_COUNT){
        return RC_ERROR;
    }

    board_[col][row] = Piece(name, color);

    return RC_SUCCESS;
}

void print_board(Board board){
    for(int row = 0; row < BOARD_ROW_COUNT; row++){
        for(int col = 0; col < BOARD_COL_COUNT; col++){
            std::cout << board.get_piece(row, col).symbol() << " ";
        }
        std::cout << std::endl;
    }
}