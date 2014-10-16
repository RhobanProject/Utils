#ifndef UTILS_TIMING_BENCHMARK_HPP
#define UTILS_TIMING_BENCHMARK_HPP

#include <chrono>
#include <map>
#include <vector>


// TODO: create an example tests for this class

namespace Utils {
  namespace Timing {

    class Benchmark
    {
    private:
      /* Static variables */
      static Benchmark * current;

      // typedefs
      typedef std::chrono::time_point<std::chrono::steady_clock> TimeStamp;
      typedef std::pair<std::string, TimeStamp> namedTS;
      typedef std::pair<std::string, double> namedTime;//In seconds
      typedef std::pair<std::string, Benchmark *> namedBenchmark;
      /* Local variables */
      Benchmark * father;
      std::string name;
      TimeStamp openingTime;
      TimeStamp closingTime;
      bool isTimerActive;
      namedTS currentTimer;
      std::vector<namedBenchmark> children;
      std::vector<namedTime> finishedTimers;

      static Benchmark * getCurrent();

      void print();
      void print(int depth, int width);

      double getTime() const;
      double getSubTime() const;

    public:
      Benchmark(Benchmark * father, const std::string & name);

      /**
       * Open a new benchmark or subBenchmark
       * It is not recommended to open several subBenchmark with the same name
       */
      static void open(const std::string& benchmarkName);

      /**
       * Close current benchmark or subBenchmark and return to previous context
       * if needed
       */
      static void close(bool print = false);

      /**
       * Take a timestamp associated with timingName and place it into the
       * current benchmark
       */
      static void start(const std::string& timingName);

      /**
       * End last timing and start a new one named newTimingName
       * throw an exception if there were no timing started
       */
      static void r(const std::string& newTimingName);

      /**
       * End the last timing which started for the current benchmark
       * throw an exception if there were no timing started
       */
      static void end();
    };
  }
}

#endif//UTILS_TIMING_BENCHMARK_HPP
