#include "CppUTest/CommandLineTestRunner.h"
//#include "CppUTest/TestPlugin.h"
//#include "CppUTest/TestRegistry.h"
//#include "Helper/Assertion.h"

//#include "nucleo_l496zg.h"

int main(int ac, char** av)
{
    //initialize_device();
    //delay_start(100);

#ifdef TEAMCITY_FORMAT
    // The option -oteamcity is given as argument when running in continuous integration
    static char teamcity_switch[] = "-oteamcity";
    static char *temp[2] = {nullptr, teamcity_switch };
    av = temp;
    ac = 2;

#else
    ac = 0;
    av = nullptr;
#endif
    //HelperAssertion();    // configure assertions


    CommandLineTestRunner::RunAllTests(ac, av);
    //print("\nEND-OF-FIRMWARE\n");
}

#ifdef __arm__

#endif

