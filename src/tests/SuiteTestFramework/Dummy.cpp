#include "CppUTest/TestHarness.h"

TEST_GROUP(Dummy){

void setup(void){

}

void teardown(void){

}

};

TEST(Dummy, test_that_fails){
    BYTES_EQUAL(1, 0);
}