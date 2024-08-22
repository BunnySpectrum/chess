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

typedef struct MoveRequest{
    Location locStart;
    Location locEnd;
}MoveRequest_s;

class Player{
    public:
        Player(PieceColor_e color);
        virtual std::optional<MoveRequest_s> pick_move(const Board& board) = 0;
        virtual ~Player() = default;

    protected:
        PieceColor_e color_;
};

class HumanPlayer final : public Player{
    public:
        HumanPlayer(PieceColor_e color);
        std::optional<MoveRequest_s> pick_move(const Board& board);
};

class CpuPlayer final : public Player{
    public:
        CpuPlayer(PieceColor_e color);
        std::optional<MoveRequest_s> pick_move(const Board& board);
};

class Game{
    public:
        Game();
        void Run();

    private:
        Board board;
};