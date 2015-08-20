#include "TimeStampTest.h"

#include <unistd.h>

#include "tests/runTests.h"
#include "timing/TimeStamp.hpp"

using Utils::Timing::TimeStamp;

int main(){
  runTests<TimeStampTest>("Testing TimeStamp");
}

void  TimeStampTest::_run(){
  TimeStamp start = TimeStamp::now();
  int sleepingTime = 4500;
  usleep(sleepingTime);
  TimeStamp end = TimeStamp::now();
  double elapsedTime = diffSec(start, end);
  double diff2 = (end.getTimeMS() - start.getTimeMS()) / 1000;
  assertEqualsDelta(elapsedTime, sleepingTime / 1000000.0, 0.2 / 1000.0);
  assertEqualsDelta(diff2      , sleepingTime / 1000000.0, 0.2 / 1000.0);
  assertEqualsDelta(elapsedTime, diff2, 1.0 / 1000000000);
}
