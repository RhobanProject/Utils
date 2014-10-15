#ifndef UTILS_TIMING_BENCHMARK_HPP
#define UTILS_TIMING_BENCHMARK_HPP

#include <chrono>


// TODO: create an example tests for this class

namespace Utils {
  namespace Timing {

    class Benchmark
    {
    private:
      /* Static variables */
      static std::map<std::string, Benchmark> benchmarks;
      static std::map<std::string, bool> benchmarksStatus;

      typedef time_point<std::chrono::steady_clock> TimeStamp;
      typedef std::pair<std::string, TimeStamp> namedTS;
      typedef std::pair<std::string, double> namedTime;//In seconds
      /* Local variables */
      std::vector<namedTS> pendingTimers;
      std::vector<namedTime> finishedTimers;

      /* Should only be called by getBenchmark */
      Benchmark(const std::string& benchmarkName);

      static Benchmark& getBenchmark(const std::string& name);

    public:

      /**
       * Take a timestamp associated with timingName and place it into the
       * benchmark of the given name
       */
      static void start(const std::string& benchmarkName,
                        const std::string& timingName);

      /**
       * End last timing and start a new one with timingName
       * throw an exception if there were no timing started
       */
      static void reNew(const std::string& benchmarkName,
                        const std::string& newTimingName);

      /**
       * End the last timing which started for the given benchmark
       * throw an exception if there were no timing started
       */
      static void end(const std::string& benchmarkName);

      /**
       * Set the benchmark status (activated, disabled)
       */
      static void setStatus(const std::string& benchmarkName, bool activated);

      /**
       * Get the benchmark status (activated, disabled)
       */
      static void getStatus(const std::string& benchmarkName);

      

    };
  }
}

#endif//UTILS_TIMING_BENCHMARK_HPP
