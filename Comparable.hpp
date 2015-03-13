#ifndef RHOBAN_COMPARABLE_HPP
#define RHOBAN_COMPARABLE_HPP

#include <typeinfo>

namespace Rhoban {
  class Comparable{
  public:
    bool operator==(const Comparable & other) const
      {
        // make sure the types are the same
        if(typeid(*this) != typeid(other))
          return false;
        // if they are the same, then compare them
        return equals(other);
      }
    
  protected:
    virtual bool equals(const  Comparable & other) const = 0;
  };
}
#endif//RHOBAN_COMPARABLE_HPP
