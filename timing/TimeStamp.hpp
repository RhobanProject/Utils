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

      double getTimeMS() const;
    };

  }
}

double diffSec(const Utils::Timing::TimeStamp & src,
               const Utils::Timing::TimeStamp & dst);
double diffMs(const Utils::Timing::TimeStamp & src,
              const Utils::Timing::TimeStamp & dst);

#endif//UTILS_TIMING_TIMESTAMP_HPP
