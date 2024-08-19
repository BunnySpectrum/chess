#pragma once

#include "app/board.h"
#include "app/piece.h"
#include "utils/codes.h"
#include <vector>
#include <array>

typedef enum SearchDirection{
    SEARCH_UP = 0,
    SEARCH_UPRIGHT,
    SEARCH_RIGHT,
    SEARCH_DOWNRIGHT,
    SEARCH_DOWN,
    SEARCH_DOWNLEFT,
    SEARCH_LEFT,
    SEARCH_UPLEFT,
}SearchDirection_e;

ReturnCode_e move_piece(Board* board, Location startLoc, Location endLoc);

std::vector<Location> valid_moves_for_pawn(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_rook(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_knight(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_bishop(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_king(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_queen(const Board* pBoard, Location startLoc);

std::vector<Location> valid_moves_for_piece(const Board& board, Location startLoc);