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

      void printCSV(std::ostream & out, int depth, int maxDepth = -1);

      static void printCSVHeader(std::ostream & out);

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
       * provided name.
       * /!\ char * is used instead of string here. Otherwise, if we call close("any string")
       * the compiler choses the close(bool) overload instead of this one. Great job
       * c++
       */
      static double close(const char * expectedName, bool print = false,
                          int detailLevel = -1, std::ostream & out = std::cout);

      /**
       * Close the current benchmak and print its output to the file at the
       * given path.
       */
      static double closeCSV(const std::string & path, int detailLevel = -1);
      /**
       * close the current benchmark and append its content to the provided
       * output stream, csv header is printed or not according to the related
       * parameter
       */
      static double closeCSV(std::ostream & out, bool header, int detailLevel = -1);
    };
  }
}
