#pragma once

#include "app/board.h"
#include "app/piece.h"
#include "utils/codes.h"

ReturnCode_e move_piece(Board* board, Location startLoc, Location endLoc);
