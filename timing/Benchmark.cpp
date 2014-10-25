#include "Benchmark.hpp"

#include <algorithm>
#include <exception>
#include <iomanip>
#include <iostream>
#include <tuple>

using namespace std::chrono;

namespace Utils {
  namespace Timing {

    /* Static variables */
    Benchmark * Benchmark::current = NULL;

    Benchmark::Benchmark(Benchmark * f, const std::string & n)
      : father(f), name(n)
    {
#ifndef WIN32
      openingTime = steady_clock::now();
#endif
      isTimerActive = false;
    }

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

    void Benchmark::close(bool print)
    {
      if (current == NULL)
        throw std::runtime_error("No active benchmark to close");
      Benchmark * toClose = current;
#ifndef WIN32
      toClose->closingTime = steady_clock::now();
#endif
      current = toClose->father;
      if (print)
        toClose->print();
      // Suppress Benchmark if the link is lost
      if (current == NULL)
        delete(toClose);
    }

    double Benchmark::getTime() const
    {
      double elapsedTicks = double((closingTime - openingTime).count());
      double time = elapsedTicks * steady_clock::period::num / steady_clock::period::den;
      return time;
      
    }

    double Benchmark::getSubTime() const
    {
      double t = 0;
      for (auto& c : children) {
        t += c.second->getTime();
      }
      return t;
    }


    // Printable data: <name, elapsedTime, link>
    typedef std::tuple<std::string, double, Benchmark *> printableEntry;
    int cmp(const printableEntry& a,
            const printableEntry& b)
    {
      return std::get<1>(a) < std::get<1>(b);
    }

    void Benchmark::print()
    {
      // Formatting specifically
      int precision = 3;
      int width = 8;
      int oldPrecision = std::cout.precision();
      std::cout.precision(precision);
      std::cout.setf(std::ios::fixed, std::ios::floatfield);

      print(0, width);

      // Restoring default
      std::cout.precision(oldPrecision);
      std::cout.unsetf(std::ios::floatfield);
    }

    void Benchmark::print(int depth, int width)
    {
      // Build and sort printable data
      typedef std::tuple<std::string, double, Benchmark *> printableEntry;
      std::vector<printableEntry> subFields;
      for(auto& c : children) {
        subFields.push_back(printableEntry(c.first,
                                           c.second->getTime(),
                                           c.second));
      }
      // Add Unknown field only if there are other information
      if (subFields.size() > 0) {
        subFields.push_back(printableEntry("Unknown",
                                           getTime() - getSubTime(),
                                           NULL));
      }
      // Ordering
      std::sort(subFields.begin(), subFields.end(), cmp);
      // Printing
      for(auto& f : subFields) {
        // For Benchmark, print them
        if (std::get<2>(f) != NULL){
          std::get<2>(f)->print(depth + 1, width);
        }
        // Print entries
        else {
          for (int i = 0; i < depth + 1; i++) std::cout << '\t';
          std::cout << std::setw(width) << (std::get<1>(f) * 1000) << " ms : "
                    << std::get<0>(f) << std::endl;
        }
      }
      for (int i = 0; i < depth; i++) std::cout << '\t';
      std::cout << std::setw(width) << getTime() * 1000 << " ms : "
                << name << std::endl;
    }
  }
}
