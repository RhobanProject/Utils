#include <unordered_set>
#include <unordered_map>

namespace Rhoban {

  template<class T>
  struct ValueBasedHash {
    size_t operator () (const T * t) const
      { return std::hash<T>()(*t); }
  };

  template<class T>
  struct ValueBasedEquality {
    bool operator () (const T * t1, const T * t2) const
      { return *t1 == *t2; }
  };

  template <class T>
  using unordered_pointer_set = std::unordered_set<T *,
                                                   ValueBasedHash<T>,
                                                   ValueBasedEquality<T>>;

  template <class T, class A>
  using unordered_pointer_map = std::unordered_map<T *, A,
                                                   ValueBasedHash<T>,
                                                   ValueBasedEquality<T>>;

}
