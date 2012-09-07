#include <cstdio>
#include <cstdlib>
#include "Something.h"
#include "ConfigFile.h"

void printSomething(Something &something)
{
    printf("* Something:\n");
    printf("int: %d\n", something.intParam);
    printf("str: %s\n", something.stringParam.c_str());
    printf("float: %f\n", something.floatParam);
    printf("bool: %d\n", something.boolParam ? 1 : 0);
}

int main(int argc, char **argv)
{
    Something something, something2;
    ConfigFile config("config.yml");
    config.processCommandArgs(argc, argv);

    config.loadSomething(&something);
    printSomething(something);

    config.loadSomething2(&something2);
    printSomething(something2);
}
