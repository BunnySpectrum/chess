
#include "test_location.h"

void test_Location_invalid(void)
{
    Location loc = Location();
  TEST_ASSERT_TRUE(loc.is_invalid());
}

void test_Location_valid(void)
{
    Location loc = Location(2,2);
  TEST_ASSERT_FALSE(loc.is_invalid());
}

void test_Location_row(void)
{
    int row = 2;
    int col = 3;
    Location loc = Location(row, col);
  TEST_ASSERT_EQUAL(row, loc.row());
}

void test_Location_col(void)
{
    int row = 2;
    int col = 3;
    Location loc = Location(row, col);
  TEST_ASSERT_EQUAL(col, loc.col());
}


void test_location(void){
    RUN_TEST(test_Location_invalid);
    RUN_TEST(test_Location_valid);
    RUN_TEST(test_Location_row);
    RUN_TEST(test_Location_col);
}