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

// bool is_valid_move(Board board, Location startLoc, Location endLoc){
//     auto startPiece = board.get_piece(startLoc);
//     auto endPiece = board.get_piece(endLoc);

//     if(startLoc.is_invalid() || endLoc.is_invalid()){
//         return false;
//     }

//     // Rule 0: can't capture your own piece
//     if((endPiece.id() != PIECE_NOTHING) && (startPiece.color() == endPiece.color()) ){
//         std::cout << "Can't capture own piece" << std::endl;
//         return false;
//     }

//     int deltaRow = abs(startLoc.row() - endLoc.row());
//     int deltaCol = abs(startLoc.col() - endLoc.col());
//     bool isDiagonal = deltaRow == deltaCol;

//     return false;
// }

std::vector<Location> valid_moves_for_piece(const Board& board, Location loc){
    if(loc.is_invalid()){
        return {};
    }

    Piece piece = board.get_piece(loc);
    switch(piece.id()){
        case PIECE_NOTHING:
            return {};

        case PIECE_PAWN:
        case PIECE_PAWN_FIRST:
            return valid_moves_for_pawn(&board, loc);

        case PIECE_ROOK:
        case PIECE_ROOK_FIRST:
            return valid_moves_for_rook(&board, loc);

        case PIECE_KNIGHT:
            return valid_moves_for_knight(&board, loc);
        
        case PIECE_BISHOP:
            return valid_moves_for_bishop(&board, loc);

        case PIECE_QUEEN:
            return valid_moves_for_queen(&board, loc);

        case PIECE_KING:
        case PIECE_KING_FIRST:
            return valid_moves_for_king(&board, loc);

        default:
            std::cout << "[Error] unhandled piece: " << piece << std::endl;
            return {};    
    }

}

static std::vector<Location> find_moves_line(const Board* pBoard, Location startLoc, SearchDirection_e dir){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol, rowInc, colInc;

    switch(dir){
        case SEARCH_UP:
            rowInc = -1;
            colInc = 0;
            break;
        case SEARCH_UPRIGHT:
            rowInc = -1;
            colInc = 1;
            break;
        case SEARCH_RIGHT:
            rowInc = 0;
            colInc = 1;
            break;
        case SEARCH_DOWNRIGHT:
            rowInc = 1;
            colInc = 1;
            break;
        case SEARCH_DOWN:
            rowInc = 1;
            colInc = 0;
            break;
        case SEARCH_DOWNLEFT:
            rowInc = 1;
            colInc = -1;
            break;
        case SEARCH_LEFT:
            rowInc = 0;
            colInc = -1;
            break;
        case SEARCH_UPLEFT:
            rowInc = -1;
            colInc = -1;
            break;
        default:
            std::cout << "Unexpected direction: " << dir << std::endl;
            return result;
    }

    startPiece = pBoard->get_piece(startLoc);
    deltaRow = rowInc;
    deltaCol = colInc;
    testLoc = Location(startLoc.row() + deltaRow, startLoc.col() + deltaCol);
    while(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() == PIECE_NOTHING)){
            result.push_back(testLoc);
        }else{
            if(testPiece.color() != startPiece.color()){
                result.push_back(testLoc);
            }
            break;
        }
        deltaRow += rowInc;
        deltaCol += colInc;
        testLoc = Location(startLoc.row() + deltaRow, startLoc.col() + deltaCol);
    }
    return result;
}


std::vector<Location> valid_moves_for_pawn(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;

    startPiece = pBoard->get_piece(startLoc);
    int direction = startPiece.color() == COLOR_WHITE ? -1 : 1;
    // std::cout << "Testing piece: " << startPiece << std::endl;

    // right-diagonal
    testLoc = Location(startLoc.row() + direction, startLoc.col() + 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) && (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    // left-diagonal
    testLoc = Location(startLoc.row() + direction, startLoc.col() - 1);
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() != PIECE_NOTHING) && (testPiece.color() != startPiece.color())){
            result.push_back(testLoc);
        }
    }

    // step forward
    testLoc = Location(startLoc.row() + direction, startLoc.col());
    if(!testLoc.is_invalid()){
        testPiece = pBoard->get_piece(testLoc);
        if( (testPiece.id() == PIECE_NOTHING) ){
            result.push_back(testLoc);
        }
    }

    // two steps if first
    if(startPiece.id() == PIECE_PAWN_FIRST){
        testLoc = Location(startLoc.row() + 2*direction, startLoc.col());
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
    Piece testPiece, startPiece;

    startPiece = pBoard->get_piece(startLoc);
    // std::cout << "Testing piece: " << startPiece << std::endl;

    std::array<SearchDirection_e, 4> directions = {SEARCH_UP, SEARCH_RIGHT, SEARCH_DOWN, SEARCH_LEFT};

    for(const SearchDirection_e dir : directions){
        for(const Location& loc : find_moves_line(pBoard, startLoc, dir)){
            result.push_back(loc);
        }
    }

    return result;
}
std::vector<Location> valid_moves_for_knight(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;

    startPiece = pBoard->get_piece(startLoc);
    // std::cout << "Testing piece: " << startPiece << std::endl;

    std::vector<Location> locationsToTest{
        {startLoc.row() + 2, startLoc.col() + 1}, 
        {startLoc.row() + 2, startLoc.col() - 1}, 
        {startLoc.row() - 2, startLoc.col() + 1}, 
        {startLoc.row() - 2, startLoc.col() - 1}, 
        {startLoc.row() + 1, startLoc.col() + 2}, 
        {startLoc.row() - 1, startLoc.col() + 2}, 
        {startLoc.row() + 1, startLoc.col() - 2}, 
        {startLoc.row() - 1, startLoc.col() - 2}};

    for(const Location& testLoc : locationsToTest ){
        if(!testLoc.is_invalid()){
            testPiece = pBoard->get_piece(testLoc);
            if( (testPiece.id() != PIECE_NOTHING)){
                if(testPiece.color() != startPiece.color()){
                    result.push_back(testLoc);
                }
            }else{
                result.push_back(testLoc);
            }
        }
    }

    return result;
}



std::vector<Location> valid_moves_for_bishop(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;
    std::array<SearchDirection_e, 4> directions = {SEARCH_UPRIGHT, SEARCH_DOWNRIGHT, SEARCH_DOWNLEFT, SEARCH_UPLEFT};

    startPiece = pBoard->get_piece(startLoc);
    // std::cout << "Testing piece (again): " << startPiece << std::endl;

    for(const SearchDirection_e dir : directions){
        for(const Location& loc : find_moves_line(pBoard, startLoc, dir)){
            result.push_back(loc);
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
    // std::cout << "Testing piece: " << startPiece << std::endl;
    for(deltaRow = -1; deltaRow < 2; deltaRow++){
        for(deltaCol = -1; deltaCol < 2; deltaCol++){
            if((deltaRow == 0) && (deltaCol == 0)){
                continue;
            }
            testLoc = Location(startLoc.row() + deltaRow, startLoc.col() + deltaCol);
            if(!testLoc.is_invalid()){
                testPiece = pBoard->get_piece(testLoc);
                if( (testPiece.id() != PIECE_NOTHING) || (testPiece.color() != startPiece.color())){
                    result.push_back(testLoc);
                }
            }
        }
    }

    return result;
}

std::vector<Location> valid_moves_for_queen(const Board* pBoard, Location startLoc){
    auto result = std::vector<Location>();
    Location testLoc;
    Piece testPiece, startPiece;
    int deltaRow, deltaCol;
    std::array<SearchDirection_e, 8> directions = {
        SEARCH_UPRIGHT, SEARCH_DOWNRIGHT, SEARCH_DOWNLEFT, SEARCH_UPLEFT,
        SEARCH_UP, SEARCH_RIGHT, SEARCH_DOWN, SEARCH_LEFT,
        };

    startPiece = pBoard->get_piece(startLoc);
    // std::cout << "Testing piece: " << startPiece << std::endl;

    for(const SearchDirection_e dir : directions){
        for(const Location& loc : find_moves_line(pBoard, startLoc, dir)){
            result.push_back(loc);
        }
    }
    return result;
}