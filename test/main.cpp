#include <iostream>

#include "tests/runTests.h"

#include "LoggingTest.h"
#include "SocketsTest.h"
#include "TimedThreadTest.h"
#include "TestCaseTest.h"

#include <timing/TickMachine.h>

int main()
{
    TickMachine::get_tick_machine(); // FIXME: Without this, the test fails

    runTests<TestCaseTest>("Testing test");
    runTests<LoggingTest>("Testing logging");
    runTests<SocketsTest>("Testing sockets");
    runTests<TimedThreadTest>("Testing timed thread");
}
