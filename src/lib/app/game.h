#pragma once

#include "app/piece.h"
#include "app/actor.h"
#include <optional>

enum class InputState{
    Start,
    First,
    Delim,
    Second,
    End
};

typedef struct InputTokens{
    std::string leftToken;
    std::string rightToken;
}InputToken_s;

// Represents a movement on the board
//  same_team, if set, means wheter the end location color piece matches start
// Things to add? Doing so would allow moves to be reversed
//      - the piece making the move
//      - the piece, if any, that will be captured
//      - metrics: like how long it took to calc
typedef struct MoveRequest{
    Location locStart;
    Location locEnd;
    Piece pieceStart;
    Piece pieceEnd;
    int32_t score;
    std::string desc(){
        std::string result;
        result += pieceNameToString(pieceStart.id()) + " to ";
        result += locationToAlg(locEnd);
        return result;
    }
}MoveRequest_s;
// AIChess uses the start/endPiece.color to determine if a move is a protect
// or threat. It also has a 'real' bool for if the move is a legal move (i.e. not protect).
/*
    move is valid if endPiece.id == Nothing or endPiece.color != startPiece.color

    if move.same_team.has_valus()
        // end location has a piece. could also check w/ endPiece.id != nothing
    else:
        // end location is empty, therefore a valid move

*/

class Player{
    public:
        Player(PieceColor_e color);
        virtual ~Player() = default;
        virtual std::optional<MoveRequest_s> pick_move(const Board& board) = 0;
        // virtual int32_t score(const Board& board) = 0;

    protected:
        PieceColor_e color_;
};

class HumanPlayer final : public Player{
    public:
        HumanPlayer(PieceColor_e color);
        std::optional<MoveRequest_s> pick_move(const Board& board);
        // int32_t score(const Board& board);
};

class CpuPlayer final : public Player{
    public:
        CpuPlayer(PieceColor_e color);
        std::optional<MoveRequest_s> pick_move(const Board& board);
        int32_t score(const Board& board, PieceColor_e color);
        std::optional<MoveRequest_s> search_for_move(const Board& board, int depth, bool self);
    
    private:
        int max_search_depth;
};

class Game{
    public:
        Game();
        void Run();

    private:
        Board board;
};