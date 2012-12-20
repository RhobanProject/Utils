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

#include <tests/TestCase.h>

using namespace std;

class LoggingTest : public TestCase
{
    public:
        void testLogging() {
            LOG(1, 1, "main", "C-style log [%d]", 12);
            LOG_CPP(1, 1, "main", "C++-style log [" << 12 << "]");
        }

    protected:
        void _run() {
            testLogging();
        }
};
