
#pragma once

#include <iostream>
#include <memory>
#include <utility>

#include "my_shared_ptr.h"

// greedy_shared_ptr is a smart pointer that extends the functionality of
// std::shared_ptr by adding an copy assignement and contructor that accepts a
// raw pointer and takes ownership of the raw pointer.
//
// It is usually not a good idea to mix raw and smart shared pointers, because
// it is not clear who owns the raw pointer. However, in the case of a
// greedy_shared_ptr, it is clear that the greedy_shared_ptr owns the raw
// pointer.

namespace mymemory {
template <typename T> class greedy_shared_ptr : public my_shared_ptr<T> {

public:
  // Default constructor
  greedy_shared_ptr() : my_shared_ptr<T>() {}
  greedy_shared_ptr(T *&&ptr) : my_shared_ptr<T>(ptr) {
    ptr = nullptr;
  }; // overrides my_shared_ptr(T *ptr)
  greedy_shared_ptr(const T *&&ptr) : my_shared_ptr<T>(ptr) {
    ptr = nullptr;
  }; // overrides my_shared_ptr &operator=(T *ptr)

}; // class greedy_shared_ptr
} // namespace mymemory
