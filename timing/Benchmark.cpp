#include "Benchmark.hpp"

#include <exception>

using namespace std::chrono;

namespace Utils {
  namespace Timing {

    /* Static variables */
    std::map<std::string, Benchmark> Benchmark::benchmarks;
    std::map<std::string, bool> Benchmark::benchmarksStatus;

    Benchmark::Benchmark(const std::string& benchmarkName)
    {
    }

    Benchmark& Benchmark::getBenchmark(const std::string name)
    {
      // Throw an error if there is already an entry with the same name
      try {
        return benchmarks.at(benchmarkName);
      }
      catch (std::out_of_range e){
        Benchmark b(name);
        benchmarks[name] = b;
        benchmarksStatus[name] = true;
        return b;
      }
    }

    void Benchmark::start(const std::string& benchmarkName,
                          const std::string& timingName)
    {
      Benchmark& b = getBenchmark(benchmarkName);
      if (!getStatus(benchmarkName)) return;
      namedTS newEntry = namedTS(timingName, steady_clock::now());
      b.pendingTimers.push_back(newEntry);
    }

    void Benchmark::end(const std::string& benchmarkName)
    {
      Benchmark& b = getBenchmark(benchmarkName);
      if (!getStatus(benchmarkName)) return;
      if (b.pendingTimers.size() == 0)
        throw std::runtime_error("No timer to end!");
      namedTS start = b.pendingTimers.back();
      TimeStamp now = steady_clock.now;
      b.pendingTimers.pop_back();
      double elapsedTicks = double((now - start.second).count());
      double time = elapsedTicks * steady_clock::period::num / steady_clock::period::den;
      namedTime timeEntry(start.first, time);
      b.finishedTimers.push_back(timeEntry);
    }

    void Benchmark::reNew(const std::string& benchmarkName,
                          const std::string& newTimingName)
    {
      end(benchmarkName);
      start(benchmarkName, newTimingName);
    }
    
    void Benchmark::setStatus(const std::string& benchmarkName, bool activated)
    {
      // Create benchmark if required
      getBenchmark(benchmarkName);
      benchmarksStatus[benchmarkName] = activated;
    }
    
    void Benchmark::getStatus(const std::string& benchmarkName)
    {
      // Create benchmark if required
      getBenchmark(benchmarkName);
      return benchmarksStatus[benchmarkName];
    }

    void Benchmark::print(const std::string& benchmarkName)
    {
      //TODO
    }
  }
}
