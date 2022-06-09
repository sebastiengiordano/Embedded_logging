#include "CppUTest/CommandLineTestRunner.h"
//#include "CppUTest/TestPlugin.h"
//#include "CppUTest/TestRegistry.h"
//#include "Helper/Assertion.h"



int main(int ac, char** av)
{
    //HelperAssertion();    // configure assertions
    // The option -oteamcity is given as argument when running in continuous integration
    return CommandLineTestRunner::RunAllTests(ac, av);
}