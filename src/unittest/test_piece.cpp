
#include "test_piece.h"

void test_piece_first_move(void)
{
  auto king = Piece(PIECE_KING_FIRST, COLOR_WHITE, Location(3, 3));
  king.move(Location(3,4));
  TEST_ASSERT_EQUAL(PIECE_KING, king.id());

  auto rook = Piece(PIECE_ROOK_FIRST, COLOR_WHITE, Location(3, 3));
  rook.move(Location(3,4));
  TEST_ASSERT_EQUAL(PIECE_ROOK, rook.id());

  auto pawn = Piece(PIECE_PAWN_FIRST, COLOR_WHITE, Location(3, 3));
  pawn.move(Location(3,4));
  TEST_ASSERT_EQUAL(PIECE_PAWN, pawn.id());

}


void test_piece(void){
    RUN_TEST(test_piece_first_move);
}