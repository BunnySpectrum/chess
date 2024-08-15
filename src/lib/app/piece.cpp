
#include "piece.h"

Location::Location():
row_(-1),
col_(-1){
    ;
}

Location::Location(int row, int col):
row_(row),
col_(col){
    ;
}

int Location::row() const{
    return row_;
}

int Location::col() const{
    return col_;
}
        
bool Location::is_invalid() const{
    if( (this->row_ < 0) || (this->row_ >= BOARD_ROW_COUNT) || (this->col_ < 0) || (this->col_ >= BOARD_ROW_COUNT)){
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, Location const &loc){
    return os << loc.row() << ":" << loc.col();
}

bool Location::operator==(const Location &otherLoc) const{
    if( (this->row() == otherLoc.row()) && (this->col() == otherLoc.col())){
        return true;
    }else{
        return false;
    }
}


// -----------------------------

// std::string Location::repr(){
//     return "row " + row_ + ", col " + col_;
// }

std::string pieceNameToString(PieceName_e piece){
    switch(piece){
        case PIECE_NOTHING:
            return "nothing";
        case PIECE_PAWN:
            return "pawn";
        case PIECE_PAWN_FIRST:
            return "pawn-f";
        case PIECE_ROOK:
            return "rook";
        case PIECE_ROOK_FIRST:
            return "rook-f";
        case PIECE_KNIGHT:
            return "knight";
        case PIECE_BISHOP:
            return "bishop";
        case PIECE_QUEEN:
            return "queen";
        case PIECE_KING:
            return "king";
        case PIECE_KING_FIRST:
            return "king-f";
        default:
            return "ERR";
    }
}

std::string pieceNameToSymbol(PieceName_e piece){
    switch(piece){
        case PIECE_NOTHING:
            return ".";
        case PIECE_PAWN:
            return "P";
        case PIECE_PAWN_FIRST:
            return "p";
        case PIECE_ROOK:
            return "R";
        case PIECE_ROOK_FIRST:
            return "r";
        case PIECE_KNIGHT:
            return "N";
        case PIECE_BISHOP:
            return "B";
        case PIECE_QUEEN:
            return "Q";
        case PIECE_KING:
            return "K";
        case PIECE_KING_FIRST:
            return "k";
        default:
            return "ERR";
    }
}

std::string pieceColorToSymbol(PieceColor_e color){
    switch(color){
        case COLOR_BLACK:
            return "b";
        case COLOR_WHITE:
            return "w";
        default:
            return "x";
    }
}

Piece::Piece(){
    id_ = PIECE_NOTHING;
    color_ = COLOR_WHITE;
    loc_ = Location(-1, -1);
};

Piece::Piece(PieceName_e id, PieceColor_e color, Location loc): 
id_(id),
color_(color),
loc_(loc){
    ;
}

// Piece::Piece(PieceName_e id, Location loc): 
// id_(id),
// loc_(loc){
//     ;
// }

PieceName_e Piece::id() const{
    return id_;
}

PieceColor_e Piece::color() const{
    return color_;
}

std::string Piece::symbol() const{
    if(this->id() == PIECE_NOTHING){
        return ' ' + pieceNameToSymbol(this->id());
    }else{
        return pieceNameToSymbol(this->id()) + pieceColorToSymbol(this->color());
    }
}

Location Piece::location() const{
    return loc_;
}

ReturnCode_e Piece::move(Location newLoc){

    // determine id for new destination piece
    auto newID = PIECE_NOTHING;
    switch(this->id()){
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
            newID = this->id();
            break;
    }
    this->id_ = newID;
    return RC_SUCCESS;
}



std::ostream &operator<<(std::ostream &os, Piece const &piece){
    return os << piece.symbol() << " at " << piece.location();
}

bool Piece::operator==(const Piece &otherPiece) const{
    if( (this->location() == otherPiece.location()) && 
        (this->id() == otherPiece.id()) &&
        (this->color() == otherPiece.color()) ){
        return true;
    }else{
        return false;
    }
}

// std::ostream &operator<<(std::ostream os, Piece const &piece){
//     return os << " at ";// << piece.loc;
// }

// void print_piece(Piece piece){
//     std::cout << pieceNameToString(piece.id()) << " at " << piece.location().row() << ", " << piece.location().col() << std::endl;
// }
