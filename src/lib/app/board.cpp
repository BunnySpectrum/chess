#include "board.h"

void init_standard_board(Board* pBoard){
    PieceColor_e color;
    Location loc;

    for(int row = 0; row < BOARD_ROW_COUNT; row++){
        color = row < 4 ? COLOR_BLACK : COLOR_WHITE;

        for(int col = 0; col < BOARD_COL_COUNT; col++){
            loc = Location(row, col);

            if(row == 1 || row == 6){
                pBoard->set_piece(loc, Piece(PIECE_PAWN_FIRST, color, loc));
            }
            else if((row==0 || row==7) && (col==0 || col==7)){
                pBoard->set_piece(loc, Piece(PIECE_ROOK_FIRST, color, loc));
            }
            else if((row==0 || row==7) && (col==1 || col==6)){
                pBoard->set_piece(loc, Piece(PIECE_KNIGHT, color, loc));
            }
            else if((row==0 || row==7) && (col==2 || col==5)){
                pBoard->set_piece(loc, Piece(PIECE_BISHOP, color, loc));
            }
            else if((row==0 || row==7) && (col==3)){
                pBoard->set_piece(loc, Piece(PIECE_QUEEN, color, loc));
            }
            else if((row==0 || row==7) && (col==4)){
                pBoard->set_piece(loc, Piece(PIECE_KING_FIRST, color, loc));
            }
            else{
                pBoard->set_piece(loc, Piece(PIECE_NOTHING, color, loc));
            }
        }
    }
}


Board::Board(){
    Location loc;

    for(int row = 0; row < BOARD_ROW_COUNT; row++){
        for(int col = 0; col < BOARD_COL_COUNT; col++){

            loc = Location(row, col);
            
            board_[col][row] = Piece(PIECE_NOTHING, COLOR_WHITE, loc);

        }
    }

}
        
Piece Board::get_piece(Location loc) const{
    if(loc.is_invalid()){
        return Piece(PIECE_NOTHING, COLOR_WHITE, loc);
    }
    return board_[loc.col()][loc.row()];
}

ReturnCode_e Board::set_piece(Location loc, Piece piece){
    if(loc.is_invalid()){
        return RC_ERROR;
    }

    board_[loc.col()][loc.row()] = piece;

    return RC_SUCCESS;
}

ReturnCode_e Board::clear_piece(Location loc){
    return this->set_piece(loc, Piece(PIECE_NOTHING, COLOR_WHITE, loc));
}

void print_board(Board board){
    std::cout << "     0  1  2  3  4  5  6  7" << std::endl;
    std::cout << "     A  B  C  D  E  F  G  H" << std::endl;
    for(int row = 0; row < BOARD_ROW_COUNT; row++){
        std::cout << row << " " << 8 - row << " ";
        for(int col = 0; col < BOARD_COL_COUNT; col++){
            std::cout << board.get_piece(Location(row, col)).symbol() << " ";
        }
        std::cout << 8 - row << " " << row;
        std::cout << std::endl;
    }
    std::cout << "     A  B  C  D  E  F  G  H" << std::endl;
    std::cout << "     0  1  2  3  4  5  6  7" << std::endl;
}