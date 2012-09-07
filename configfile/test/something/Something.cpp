#include <cstdio>
#include <string>

#include "Something.h"

using namespace std;

void Something::print()
{
    printf("Something object:\n");
    printf("int: %d\n", intParam);
    printf("str: %s\n", stringParam.c_str());
    printf("float: %f\n", floatParam);
    printf("bool: %d\n", boolParam ? 1 : 0);
}
