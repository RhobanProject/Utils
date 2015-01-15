#ifndef RHOBAN_CLONE_HPP
#define RHOBAN_CLONE_HPP

namespace Rhoban {

  // Generic function
  template<class T>
  T * clone(const T * o1){
    return o1->clone();
  }

  // Specific functions for base types
  template<>
  int * clone<int>(const int * i){
    return new int(*i);
  }
  template<>
  float * clone<float>(const float * i){
    return new float(*i);
  }
  template<>
  double * clone<double>(const double * i){
    return new double(*i);
  }
}


#endif//RHOBAN_CLONE_HPP
