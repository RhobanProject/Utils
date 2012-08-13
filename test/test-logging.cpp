/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <iostream>
#include <logging/log.h>

using namespace std;

int main(void)
{
    LOG(1, "main", "C-style log [%d]", 12);
    LOG_CPP(1, "main", "C++-style log [" << 12 << "]");
}
