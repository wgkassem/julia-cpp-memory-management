#include "greedy_shared_ptr.h"
#include "julia.h"

namespace mymemory {
template <typename T> class julia_shared_ptr : public greedy_shared_ptr<T> {

public:
  // Default constructor
  julia_shared_ptr() : greedy_shared_ptr<T>() { JL_GC_PUSH1(this->ptr); }
  julia_shared_ptr(T *&&ptr) : greedy_shared_ptr<T>(ptr) {
    ptr = nullptr;
    JL_GC_PUSH1(this->ptr);
  }; // overrides greedy_shared_ptr(T *ptr)
  julia_shared_ptr(const T *&&ptr) : greedy_shared_ptr<T>(ptr) {
    ptr = nullptr;
  }; // overrides greedy_shared_ptr &operator=(T *ptr)

  ~julia_shared_ptr() { JL_GC_POP(); }
}; // class julia_shared_ptr
} // namespace mymemory
