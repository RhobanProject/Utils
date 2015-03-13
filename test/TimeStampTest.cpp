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
  assertEqualsDelta(elapsedTime, sleepingTime / 1000000.0, 100 / 1000000.0);
}
