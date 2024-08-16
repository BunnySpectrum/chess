
#include <iostream>

#include "app/piece.h"
#include "app/board.h"
#include "app/actor.h"

#include "unity.h"
#include "test_location.h"
#include "test_piece.h"
#include "test_actor.h"

extern "C" void setUp(void){
    ;
}

extern "C" void tearDown(void){
    ;
}

int main(int argc, char* argv[]){

    UNITY_BEGIN();

    std::cout << "Running" << std::endl;
    test_location();
    test_piece();
    test_actor();

    return UNITY_END();
}