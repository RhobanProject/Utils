#include "Benchmark.hpp"

#include <exception>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

namespace Utils {
  namespace Timing {

    /* Static variables */
    std::map<std::string, Benchmark> Benchmark::benchmarks;
    std::map<std::string, bool> Benchmark::benchmarksStatus;

    Benchmark::Benchmark()
    {
      std::cout << "Initializing a benchmark" << std::endl;
    }

    Benchmark& Benchmark::getBenchmark(const std::string& name)
    {
      // Throw an error if there is already an entry with the same name
      try {
        return benchmarks.at(name);
      }
      catch (std::out_of_range e){
        Benchmark b;
        benchmarks[name] = b;
        benchmarksStatus[name] = true;
        return benchmarks[name];
      }
    }

    void Benchmark::start(const std::string& benchmarkName,
                          const std::string& timingName)
    {
      Benchmark& b = getBenchmark(benchmarkName);
      if (!isActivated(benchmarkName)) return;
      namedTS newEntry = namedTS(timingName, steady_clock::now());
      b.pendingTimers.push_back(newEntry);
    }

    void Benchmark::end(const std::string& benchmarkName)
    {
      Benchmark& b = getBenchmark(benchmarkName);
      if (!isActivated(benchmarkName)) return;
      if (b.pendingTimers.size() == 0)
        throw std::runtime_error("No timer to end!");
      namedTS start = b.pendingTimers.back();
      TimeStamp now = steady_clock::now();
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
    
    bool Benchmark::isActivated(const std::string& benchmarkName)
    {
      // Create benchmark if required
      getBenchmark(benchmarkName);
      return benchmarksStatus[benchmarkName];
    }

    void Benchmark::print(const std::string& benchmarkName)
    {
      Benchmark& b = getBenchmark(benchmarkName);
      if (!isActivated(benchmarkName)) return;

      std::cout << benchmarkName << std::endl;
      int oldPrecision = std::cout.precision();
      std::cout.precision(3);
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      for(auto& e : b.finishedTimers) {
        std::cout << std::setw(8) << (e.second * 1000) << " ms : " << e.first
                  << std::endl;
      }
      std::cout.precision(oldPrecision);
      std::cout.unsetf(std::ios::floatfield);
    }

    void Benchmark::clear(const std::string& benchmarkName)
    {
      Benchmark& b = getBenchmark(benchmarkName);
      if (!isActivated(benchmarkName)) return;

      b.pendingTimers.clear();
      b.finishedTimers.clear();
    }
  }
}
