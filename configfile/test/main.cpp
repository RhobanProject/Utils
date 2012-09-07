#include <cstdio>
#include <cstdlib>
#include "Something.h"
#include "ConfigFile.h"

int main(int argc, char **argv)
{
    Something something;
    ConfigFile config("config.yml");
    config.processCommandArgs(argc, argv);

    config.loadSomething(&something);

    printf("int: %d\n", something.intParam);
    printf("str: %s\n", something.stringParam.c_str());
    printf("float: %f\n", something.floatParam);
    printf("bool: %d\n", something.boolParam ? 1 : 0);
}
