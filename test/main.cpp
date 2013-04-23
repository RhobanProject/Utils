#include <iostream>

#include "tests/runTests.h"

#include "LoggingTest.h"
#include "SocketsTest.h"
#include "CurveTest.h"
#include "TimedThreadTest.h"
#include "TestCaseTest.h"
#include "ObserverTest.h"
#include "ConfigFileTest.h"

#include <timing/TickMachine.h>

int main()
{
    TickMachine::get_tick_machine(); // FIXME: Without this, the test fails

    /*
    runTests<TestCaseTest>("Testing test");
    runTests<ObserverTest>("Testing observer");
    runTests<CurveTest>("Testing curves");
    runTests<LoggingTest>("Testing logging");
    runTests<SocketsTest>("Testing sockets");
    runTests<TimedThreadTest>("Testing timed thread");
    */
    runTests<ConfigFileTest>("Testing configfile");
}
