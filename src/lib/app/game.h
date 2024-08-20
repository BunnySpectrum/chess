#pragma once

#include "app/piece.h"
#include "app/actor.h"

class Game{
    public:
        Game();
        void Run();

    private:
        Board board;
};