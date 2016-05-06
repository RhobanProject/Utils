#pragma once

#include <chrono>
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
// TODO: create an example tests for this class

/**
 * Currently this 'Benchmark method' is not thread-safe.
 */
namespace Utils {
  namespace Timing {

    class Benchmark
    {
    private:
      /* Static variables */
      static Benchmark * current;

      // typedefs
      typedef std::chrono::time_point<std::chrono::steady_clock> TimeStamp;
      /* Local variables */
      Benchmark * father;
      std::string name;
      TimeStamp openingTime;
      TimeStamp closingTime;
      double elapsedTicks;
      std::map<std::string, Benchmark *> children;

      static Benchmark * getCurrent();

      void print(std::ostream & out, int maxDepth = -1);
      void print(std::ostream & out, int depth, int width , int maxDepth = -1);

      // Start a new timing session
      void startSession();
      void endSession();

      double getTime() const;
      double getSubTime() const;

    public:
      Benchmark(Benchmark * father, const std::string & name);
      ~Benchmark();
      //TODO fix memory leak due to destruction of children

      /**
       * Open a new benchmark or subBenchmark
       * It is not recommended to open several subBenchmark with the same name
       */
      static void open(const std::string& benchmarkName);

      /**
       * Close current benchmark or subBenchmark and return to previous context
       * if needed
       */
      static double close(bool print = false, int detailLevel = -1,
                          std::ostream & out = std::cout);

      /**
       * Throw an error if the name of the current benchmark does not match the
       * provided name
       */
      static double close(const std::string & expectedName, bool print = false,
                          int detailLevel = -1, std::ostream & out = std::cout);
    };
  }
}
