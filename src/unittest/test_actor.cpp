
#include "test_actor.h"
#include <unordered_set>

bool check_moves(std::unordered_set<Location> *expected, std::vector<Location> *moves){
  
  for(const Location& loc : *moves){
    if(expected->find(loc) == expected->end()){
      return false;
    }
  }
  
  return true;
}


void test_actor_pawn(void)
{
  std::unordered_set<Location> expected = {
    Location(5,3),
    Location(6,3)
  };

  auto loc = Location(4,3);  
  auto board = Board();
  // init_standard_board(&board);

  auto pawn = Piece(PIECE_PAWN_FIRST, COLOR_BLACK, loc);
  
  board.set_piece(loc, pawn);

  // print_board(board);

  // auto result = std::vector<Location>();

  auto result = valid_moves_for_piece(&board, loc);
  for(const Location& loc : result){
    std::cout << loc << std::endl;
  }

  auto pass = check_moves(&expected, &result);

  TEST_ASSERT(pass);

}


void test_actor(void){
    RUN_TEST(test_actor_pawn);
}