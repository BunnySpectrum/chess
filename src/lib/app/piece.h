#pragma once

#include <string>
#include <iostream>

#include "utils/codes.h"

class Location{
    public:
        Location();
        Location(int row, int col);
        int row() const;
        int col() const;
        bool is_invalid() const;
        bool operator==(const Location &otherLoc) const;
        friend std::ostream &operator<<(std::ostream &os, Location const &loc);  


    private:
        int row_;
        int col_;
};

template<>
struct std::hash<Location>
{
    size_t operator()(const Location &loc) const{
        size_t hash = (loc.row() << 8) && loc.col();
        return hash;
    }
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
        Piece(PieceName_e id, PieceColor_e color, Location loc);
        PieceName_e id() const;
        PieceColor_e color() const;
        std::string symbol() const;
        bool operator==(const Piece &otherPiece) const;
        friend std::ostream &operator<<(std::ostream &os, Piece const &piece);  

    private:
        PieceName_e id_;
        PieceColor_e color_;
};

std::string pieceNameToString(PieceName_e piece);
std::string pieceNameToSymbol(PieceName_e piece);
std::string pieceColorToSymbol(PieceColor_e color);
bool isNewLocationValid(Piece piece, Location loc);
void print_piece(Piece piece);


template<>
struct std::hash<Piece>
{
    size_t operator()(const Piece &piece) const{
        size_t hash = (piece.color() << 8) && piece.id();
        return hash;
    }
};