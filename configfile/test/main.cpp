#include <cstdio>
#include <cstdlib>
#include "Something.h"
#include "ConfigFile.h"

int main()
{
    Something something;
    ConfigFile config("config.yml");

    config.loadSomething(&something);

    printf("%d\n", something.intParam);
}
