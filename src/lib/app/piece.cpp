
#include "piece.h"

Location::Location(int row, int col):
row_(row),
col_(col){
    ;
}

int Location::row(){
    return row_;
}

int Location::col(){
    return col_;
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
};

Piece::Piece(PieceName_e id, PieceColor_e color): 
id_(id),
color_(color){
    ;
}

// Piece::Piece(PieceName_e id, Location loc): 
// id_(id),
// loc_(loc){
//     ;
// }

PieceName_e Piece::id(){
    return id_;
}

PieceColor_e Piece::color(){
    return color_;
}

std::string Piece::symbol(){
    if(this->id() == PIECE_NOTHING){
        return ' ' + pieceNameToSymbol(this->id());
    }else{
        return pieceNameToSymbol(this->id()) + pieceColorToSymbol(this->color());
    }
}

// Location Piece::location(){
//     return loc_;
// }

// std::ostream &operator<<(std::ostream os, Piece const &piece){
//     return os << " at ";// << piece.loc;
// }

// void print_piece(Piece piece){
//     std::cout << pieceNameToString(piece.id()) << " at " << piece.location().row() << ", " << piece.location().col() << std::endl;
// }
