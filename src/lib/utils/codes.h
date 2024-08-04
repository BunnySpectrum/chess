#pragma once

typedef enum ReturnCode{
    RC_ERROR = 0,
    RC_SUCCESS = 1
} ReturnCode_e;

// I know this shouldn't be here, don't @ me :( - eventually will move this around to a better place
//  like an object/file for the game config/rules 
#define BOARD_ROW_COUNT 8
#define BOARD_COL_COUNT 8