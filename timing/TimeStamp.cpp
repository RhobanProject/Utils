#include "TimeStamp.hpp"

using namespace std::chrono;

namespace Utils {
  namespace Timing {
      
    TimeStamp::TimeStamp(const time_point<steady_clock> & timePoint)
      : time_point<steady_clock>(timePoint) {}

    TimeStamp TimeStamp::now() {
      return TimeStamp(steady_clock::now());
    }

  }
}

double diffSec(const Utils::Timing::TimeStamp & src,
               const Utils::Timing::TimeStamp & dst)
{
  int elapsedTicks = (dst - src).count();
  return (double)(elapsedTicks) * steady_clock::period::num / steady_clock::period::den;
}

double diffMs(const Utils::Timing::TimeStamp & src,
              const Utils::Timing::TimeStamp & dst)
{
  return diffSec(src, dst) * 1000;
}
