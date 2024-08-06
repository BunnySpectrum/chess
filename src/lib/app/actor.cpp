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

std::vector<Location> valid_moves_for_piece(const Board* pBoard, Location loc){
    Piece piece = pBoard->get_piece(loc);
    switch(piece.id()){
        case PIECE_NOTHING:
            return {};

        case PIECE_PAWN:
        case PIECE_PAWN_FIRST:
            return valid_moves_for_pawn(pBoard, loc);

        case PIECE_ROOK:
        case PIECE_ROOK_FIRST:
            return valid_moves_for_rook(pBoard, loc);

        case PIECE_KNIGHT:
            return valid_moves_for_knight(pBoard, loc);
        
        case PIECE_BISHOP:
            return valid_moves_for_bishop(pBoard, loc);

        case PIECE_QUEEN:
            return valid_moves_for_queen(pBoard, loc);

        case PIECE_KING:
        case PIECE_KING_FIRST:
            return valid_moves_for_king(pBoard, loc);

        default:
            std::cout << "[Error] unhandled piece: " << piece << std::endl;
            return {};    
    }

}

std::vector<Location> valid_moves_for_pawn(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;

    startPiece = pBoard->get_piece(startLoc);
    std::cout << "Testing piece: " << startPiece << std::endl;

    testLoc = Location(startLoc.row() + 1, startLoc.col() + 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    testLoc = Location(startLoc.row() + 1, startLoc.col() - 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    testLoc = Location(startLoc.row() + 1, startLoc.col());
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() == PIECE_NOTHING) ){
            result.push_back(testLoc);
        }
    }

    if(startPiece.id() == PIECE_PAWN_FIRST){
        testLoc = Location(startLoc.row() + 2, startLoc.col());
        if(!testLoc.is_invalid()){
            testPiece = pBoard->get_piece(testLoc);
            if( (testPiece.id() == PIECE_NOTHING) ){
                result.push_back(testLoc);
            }
        }
    }

    return result;
}

std::vector<Location> valid_moves_for_rook(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;

    startPiece = pBoard->get_piece(startLoc);
    std::cout << "Testing piece: " << startPiece << std::endl;

    // search ahead in rows, stay in current column
    for(deltaRow = 1; deltaRow < BOARD_ROW_COUNT; deltaRow++){
        testLoc = Location(startLoc.row() + deltaRow, startLoc.col());
        if(testLoc.is_invalid()){
            break;
        }

        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) && (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
            break;
        }
    }


    // search behind in rows, stay in current column
    for(deltaRow = -1; deltaRow >= 0; deltaRow--){
        testLoc = Location(startLoc.row() + deltaRow, startLoc.col());
        if(testLoc.is_invalid()){
            break;
        }

        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) && (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
            break;
        }
    }

    // search ahead in columns, stay in current row
    for(deltaCol = 1; deltaCol < BOARD_COL_COUNT; deltaCol++){
        testLoc = Location(startLoc.row(), startLoc.col() + deltaCol);
        if(testLoc.is_invalid()){
            break;
        }

        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) && (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
            break;
        }
    }

    // search ahead in columns, stay in current row
    for(deltaCol = -1; deltaCol >= 0; deltaCol--){
        testLoc = Location(startLoc.row(), startLoc.col() + deltaCol);
        if(testLoc.is_invalid()){
            break;
        }

        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) && (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
            break;
        }
    }


    return result;
}
std::vector<Location> valid_moves_for_knight(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;

    startPiece = pBoard->get_piece(startLoc);
    std::cout << "Testing piece: " << startPiece << std::endl;

    testLoc = Location(startLoc.row() + 1, startLoc.col() + 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    return result;
}

std::vector<Location> valid_moves_for_bishop(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;

    startPiece = pBoard->get_piece(startLoc);
    std::cout << "Testing piece: " << startPiece << std::endl;

    testLoc = Location(startLoc.row() + 1, startLoc.col() + 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    return result;
}

std::vector<Location> valid_moves_for_king(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;

    startPiece = pBoard->get_piece(startLoc);
    std::cout << "Testing piece: " << startPiece << std::endl;

    testLoc = Location(startLoc.row() + 1, startLoc.col() + 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    return result;
}

std::vector<Location> valid_moves_for_queen(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;

    startPiece = pBoard->get_piece(startLoc);
    std::cout << "Testing piece: " << startPiece << std::endl;

    testLoc = Location(startLoc.row() + 1, startLoc.col() + 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    return result;
}