#include "Benchmark.hpp"

#include <exception>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

namespace Utils {
  namespace Timing {

    /* Static variables */
    Benchmark * Benchmark::current = NULL;

    Benchmark * Benchmark::getCurrent()
    {
      if (current == NULL)
        open("Default");
      return current;
    }

    void Benchmark::open(const std::string& benchmarkName)
    {
      Benchmark * newB = new Benchmark(current, benchmarkName);
      if (current != NULL) {
        current->children.push_back(namedBenchmark(benchmarkName, newB));
      }
      current = newB;
    }

    void Benchmark::close()
    {
      if (current == NULL)
        throw std::runtime_error("No active benchmark to close");
      Benchmark * toClose = current;
      current = toClose->father;
      // Suppress Benchmark if the link is lost
      if (current == NULL)
        delete(toClose);
    }

    void Benchmark::start(const std::string& timingName)
    {
      Benchmark * b = getCurrent();

      namedTS newEntry = namedTS(timingName, steady_clock::now());
      b->pendingTimers.push_back(newEntry);
    }

    void Benchmark::end()
    {
      Benchmark * b = getCurrent();

      if (b->pendingTimers.size() == 0)
        throw std::runtime_error("No timer to end!");
      TimeStamp now = steady_clock::now();
      namedTS start = b->pendingTimers.back();
      b->pendingTimers.pop_back();
      double elapsedTicks = double((now - start.second).count());
      double time = elapsedTicks * steady_clock::period::num / steady_clock::period::den;
      namedTime timeEntry(start.first, time);
      b->finishedTimers.push_back(timeEntry);
    }

    void Benchmark::reNew(const std::string& newTimingName)
    {
      end();
      start(newTimingName);
    }

    double Benchmark::totalTime()
    {
      double t = 0;
      for (auto& e : finishedTimers){
        t += e.second;
      }
      return t;
    }

    void Benchmark::print()
    {
      int oldPrecision = std::cout.precision();
      std::cout.precision(3);
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      for(auto& e : finishedTimers) {
        std::cout << '\t'  << std::setw(8) << (e.second * 1000) << " ms : "
                  << e.first << std::endl;
      }
      std::cout << totalTime() * 1000 << " ms : " << name << std::endl;
      std::cout.precision(oldPrecision);
      std::cout.unsetf(std::ios::floatfield);
    }

    void Benchmark::printCurrent()
    {
      Benchmark * b = getCurrent();

      b->print();
    }
  }
}
