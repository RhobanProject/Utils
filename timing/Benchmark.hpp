#ifndef UTILS_TIMING_BENCHMARK_HPP
#define UTILS_TIMING_BENCHMARK_HPP

#include <chrono>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
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
      typedef std::pair<std::string, Benchmark *> namedBenchmark;
      /* Local variables */
      Benchmark * father;
      std::string name;
      TimeStamp openingTime;
      TimeStamp closingTime;
      bool isTimerActive;
      std::vector<namedBenchmark> children;

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
    };
  }
}

#endif//UTILS_TIMING_BENCHMARK_HPP
