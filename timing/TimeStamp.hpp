#ifndef UTILS_TIMING_TIMESTAMP_HPP
#define UTILS_TIMING_TIMESTAMP_HPP

#include <chrono>

namespace Utils {
  namespace Timing {

    class TimeStamp : public std::chrono::time_point<std::chrono::steady_clock> {
    private:
      TimeStamp(const std::chrono::time_point<std::chrono::steady_clock> & timePoint);

    public:
      static TimeStamp now();
    };

  }
}

double diffSec(const Utils::Timing::TimeStamp & src,
               const Utils::Timing::TimeStamp & dst);
double diffMs(const Utils::Timing::TimeStamp & src,
              const Utils::Timing::TimeStamp & dst);

#endif//UTILS_TIMING_TIMESTAMP_HPP
