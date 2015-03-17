#ifndef UTILS_TIMING_TIMESTAMP_HPP
#define UTILS_TIMING_TIMESTAMP_HPP

#include <chrono>

namespace Utils {
  namespace Timing {

    class TimeStamp : public std::chrono::time_point<std::chrono::steady_clock> {
    public:
      TimeStamp();
      TimeStamp(const std::chrono::time_point<std::chrono::steady_clock> & timePoint);
      static TimeStamp now();

      static TimeStamp fromMS(unsigned long msSinceEpoch);

      double getTimeMS() const;

    };

  }
}

double diffSec(const Utils::Timing::TimeStamp & src,
               const Utils::Timing::TimeStamp & dst);
double diffMs(const Utils::Timing::TimeStamp & src,
              const Utils::Timing::TimeStamp & dst);

bool operator<(const Utils::Timing::TimeStamp & ts1,
               const Utils::Timing::TimeStamp & ts2);
bool operator>(const Utils::Timing::TimeStamp & ts1,
               const Utils::Timing::TimeStamp & ts2);

#endif//UTILS_TIMING_TIMESTAMP_HPP
