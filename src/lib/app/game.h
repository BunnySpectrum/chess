#pragma once

#include "app/piece.h"
#include "app/actor.h"

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

typedef struct MoveRequest{
    Location locStart;
    Location locEnd;
}MoveRequest_s;

class Player{
    public:
        Player(PieceColor_e color);
        MoveRequest_s pick_move(const Board& board);

    private:
        PieceColor_e color_;
};

class Game{
    public:
        Game();
        void Run();

    private:
        Board board;
};