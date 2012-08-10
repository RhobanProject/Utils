#include <iostream>
#include "log.h"

using namespace std;

int main(void)
{
    LOG(1, "main", "C-style log [%d]", 12);
    LOG_CPP(1, "main", "C++-style log [" << 12 << "]");
}
