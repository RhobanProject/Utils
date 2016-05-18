#include "timing/Benchmark.hpp"

#include <iostream>
#include <sstream>

using Utils::Timing::Benchmark;

int main(int argc, char ** argv)
{
  int nb_loops1 = 100;
  int nb_loops2 = 10;

  Benchmark::open("GlobalLoop");
  for (int loop1 = 1; loop1 <= nb_loops1; loop1++) {
    std::ostringstream oss1;
    oss1 << "loop" << loop1;
    Benchmark::open(oss1.str());
    for (int loop2 = 1; loop2 <= nb_loops2; loop2++) {
      std::ostringstream oss2;
      oss2 << "inner_loop" << loop2;
      Benchmark::open(oss2.str());
      Benchmark::close();
    }
    Benchmark::close();
  }
  Benchmark::closeCSV(std::cout, true);
}
