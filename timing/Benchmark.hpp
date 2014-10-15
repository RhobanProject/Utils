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
      std::vector<namedBenchmark> children;
      std::vector<namedTS> pendingTimers;
      std::vector<namedTime> finishedTimers;

      static Benchmark * getCurrent();

      void print();

      double totalTime();

    public:
      Benchmark(Benchmark * f, const std::string & n) : father(f), name(n) {};

      /**
       * Open a new benchmark or subBenchmark
       * It is not recommended to open several subBenchmark with the same name
       */
      static void open(const std::string& benchmarkName);

      /**
       * Close current benchmark or subBenchmark and return to previous context
       * if needed
       */
      static void close();

      /**
       * Take a timestamp associated with timingName and place it into the
       * current benchmark
       */
      static void start(const std::string& timingName);

      /**
       * End last timing and start a new one named newTimingName
       * throw an exception if there were no timing started
       */
      static void reNew(const std::string& newTimingName);

      /**
       * End the last timing which started for the current benchmark
       * throw an exception if there were no timing started
       */
      static void end();

      /**
       * Print all informations of current benchmark
       */
      static void printCurrent();
    };
  }
}

#endif//UTILS_TIMING_BENCHMARK_HPP
