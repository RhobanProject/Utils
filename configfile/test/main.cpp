#include <cstdio>
#include <cstdlib>
#include "config/ConfigFile.h"
#include "something/Something.h"

int main(int argc, char **argv)
{
    Something something, something2;
    ConfigFile config("config.yml");
    config.processCommandArgs(argc, argv);

    config.loadSomething(&something);
    something.print();

    config.loadSomething2(&something2);
    something2.print();
}
