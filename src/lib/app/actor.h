#pragma once

#include "app/board.h"
#include "app/piece.h"
#include "utils/codes.h"
#include <vector>

ReturnCode_e move_piece(Board* board, Location startLoc, Location endLoc);
std::vector<Location> valid_moves_for_piece(const Board* pBoard, Location startLoc);

std::vector<Location> valid_moves_for_pawn(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_rook(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_knight(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_bishop(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_king(const Board* pBoard, Location startLoc);
std::vector<Location> valid_moves_for_queen(const Board* pBoard, Location startLoc);