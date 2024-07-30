#include "actor.h"

// Moves a piece so long as:
//  - end piece is not the same color as start piece
//  - start piece is a piece (i.e. can't move an empty piece to another)
// Doesn't vet that the start -> end path is legal for a piece
ReturnCode_e move_piece(Board* board, Location startLoc, Location endLoc){
    auto startPiece = board->get_piece(startLoc);
    auto endPiece = board->get_piece(endLoc);

    // first piece can't be an empty square
    if(PIECE_NOTHING == startPiece.id()){
        std::cout << "First piece can't be empty." << std::endl;
        return RC_ERROR;
    }

    // can't capture your own piece
    if((endPiece.id() != PIECE_NOTHING) && (startPiece.color() == endPiece.color()) ){
        std::cout << "Can't capture own piece" << std::endl;
        return RC_ERROR;
    }


    // clear starting location 
    board->set_piece(startLoc, Piece(PIECE_NOTHING, COLOR_WHITE));

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
    board->set_piece(endLoc, Piece(newID, startPiece.color()));

    return RC_SUCCESS;
}

