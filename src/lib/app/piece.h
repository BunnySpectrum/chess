#pragma once

#include <string>
#include <iostream>

class Location{
    public:
        Location(int row, int col);
        int row();
        int col();

    private:
        int row_;
        int col_;
};



typedef enum PieceName{
    PIECE_NOTHING = 0,
    PIECE_PAWN,
    PIECE_PAWN_FIRST,
    PIECE_ROOK,
    PIECE_ROOK_FIRST,
    PIECE_KNIGHT,
    PIECE_BISHOP,
    PIECE_QUEEN,
    PIECE_KING,
    PIECE_KING_FIRST,
}PieceName_e;

typedef enum PieceColor{
    COLOR_BLACK = 0,
    COLOR_WHITE,
}PieceColor_e;


class Piece{
    public:
        Piece();
        Piece(PieceName_e id, PieceColor_e color);
        PieceName_e id();
        PieceColor_e color();
        // Location location();
        std::string symbol();
        // std::string repr();

    private:
        PieceName_e id_;
        PieceColor_e color_;
        // Location loc_;
};

std::string pieceNameToString(PieceName_e piece);
std::string pieceNameToSymbol(PieceName_e piece);
std::string pieceColorToSymbol(PieceColor_e color);
void print_piece(Piece piece);