#include "TimeStamp.hpp"

using namespace std::chrono;

namespace Utils {
  namespace Timing {
      
    TimeStamp::TimeStamp(){}
    TimeStamp::TimeStamp(const time_point<steady_clock> & timePoint)
      : time_point<steady_clock>(timePoint) {}

    TimeStamp TimeStamp::now()
    {
      return TimeStamp(steady_clock::now());
    }

    TimeStamp TimeStamp::fromMS(unsigned long msSinceEpoch)
    {
      return TimeStamp(time_point<steady_clock>(milliseconds(msSinceEpoch)));
    }

    double TimeStamp::getTimeMS() const
    {
      return duration_cast<std::chrono::nanoseconds>(time_since_epoch()).count() / 1000000.0;
    }

  }
}

double diffSec(const Utils::Timing::TimeStamp & src,
               const Utils::Timing::TimeStamp & dst)
{
  double elapsedTicks = (dst - src).count();
  return elapsedTicks * steady_clock::period::num / steady_clock::period::den;
}

double diffMs(const Utils::Timing::TimeStamp & src,
              const Utils::Timing::TimeStamp & dst)
{
  return diffSec(src, dst) * 1000;
}


bool operator<(const Utils::Timing::TimeStamp & ts1,
               const Utils::Timing::TimeStamp & ts2)
{
  return diffMs(ts1, ts2) > 0;
}
bool operator>(const Utils::Timing::TimeStamp & ts1,
               const Utils::Timing::TimeStamp & ts2)
{
  return diffMs(ts1, ts2) < 0;
}
