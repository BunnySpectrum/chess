
#include <iostream>

#include "app/piece.h"
#include "app/board.h"
#include "app/actor.h"

#include "unity.h"

extern "C" void setUp(void){
    ;
}

extern "C" void tearDown(void){
    ;
}

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

int main(int argc, char* argv[]){

    UNITY_BEGIN();

    std::cout << "hello world." << std::endl;
    RUN_TEST(test_Location_invalid);
    RUN_TEST(test_Location_valid);

    return UNITY_END();
}