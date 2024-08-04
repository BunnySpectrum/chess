#include "actor.h"

// Moves a piece. 
//  Fails if start piece is empty
//  Doesn't vet that the start -> end path is legal for a piece
ReturnCode_e move_piece(Board* board, Location startLoc, Location endLoc){
    auto startPiece = board->get_piece(startLoc);
    auto endPiece = board->get_piece(endLoc);

    // first piece can't be an empty square
    if(PIECE_NOTHING == startPiece.id()){
        std::cout << "First piece can't be empty." << std::endl;
        return RC_ERROR;
    }



    // clear starting location 
    board->set_piece(startLoc, Piece(PIECE_NOTHING, COLOR_WHITE, startLoc));

    // determine id for new destination piece
    auto newID = PIECE_NOTHING;
    switch(startPiece.id()){
        case PIECE_PAWN_FIRST:
            newID = PIECE_PAWN;
            break;
        case PIECE_KING_FIRST:
            newID = PIECE_KING;
            break;
        case PIECE_ROOK_FIRST:
            newID = PIECE_ROOK;
            break;
        default:
            newID = startPiece.id();
            break;
    }

    // set end piece
    board->set_piece(endLoc, Piece(newID, startPiece.color(), endLoc));

    return RC_SUCCESS;
}

bool is_valid_move(Board board, Location startLoc, Location endLoc){
    auto startPiece = board.get_piece(startLoc);
    auto endPiece = board.get_piece(endLoc);

    if(startLoc.is_invalid() || endLoc.is_invalid()){
        return false;
    }

    // Rule 0: can't capture your own piece
    if((endPiece.id() != PIECE_NOTHING) && (startPiece.color() == endPiece.color()) ){
        std::cout << "Can't capture own piece" << std::endl;
        return false;
    }

    int deltaRow = abs(startLoc.row() - endLoc.row());
    int deltaCol = abs(startLoc.col() - endLoc.col());
    bool isDiagonal = deltaRow == deltaCol;

    return false;
}
