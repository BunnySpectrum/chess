
#include <iostream>

#include "app/piece.h"
#include "app/board.h"
#include "app/actor.h"

#include "unity.h"
#include "test_location.h"

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

    return UNITY_END();
}