
#include "test_actor.h"

void test_actor_pawn(void)
{
  auto loc = Location(3,3);  
  auto board = Board();
  init_standard_board(&board);

  auto pawn = Piece(PIECE_PAWN_FIRST, COLOR_WHITE, loc);
  
  board.set_piece(loc, pawn);

  print_board(board);

  // auto result = std::vector<Location>();

  auto result = valid_moves_for_piece(&board, loc);
  for(const Location& loc : result){
    std::cout << loc << std::endl;
  }

}


void test_actor(void){
    RUN_TEST(test_actor_pawn);
}