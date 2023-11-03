#pragma once

#include <iostream>
#include <memory>
#include <utility>

// my_shared_ptr is a smart pointer that retains shared ownership of an object
// through a pointer. it also has an assignment operator that accepts a raw
// pointer similar to constructor.
template <typename T> class my_shared_ptr : public std::shared_ptr<T> {

private:
  T *_ptr = nullptr;
  size_t *_count = nullptr;

public:
  // Default constructor
  my_shared_ptr() : _ptr(nullptr), _count(nullptr) {}

  // Reset
  void reset() {
    if (_ptr == nullptr)
      return;
    (*_count)--;
    if (*_count == 0) {
      delete _ptr;
      delete _count;
    }
    _ptr = nullptr;
    _count = nullptr;
  }

  // Copy Constructor
  my_shared_ptr(const my_shared_ptr<T> &rhs)
      : _ptr(rhs._ptr), _count(rhs._count) {
    (*_count)++;
  }

  // Move constructor
  my_shared_ptr(my_shared_ptr<T> &&rhs) {
    _ptr = rhs._ptr;
    _count = rhs._count;
    rhs._ptr = nullptr;
    rhs._count = nullptr;
  }

  // Copy Assignment using copy-and-swap idiom
  my_shared_ptr<T> &operator=(const my_shared_ptr<T> &rhs) {
    if (this != &rhs) {
      this->reset(); // Release the current resource
      // Copy the data and the count pointer, and increment the shared count
      _ptr = rhs._ptr;
      _count = rhs._count;
      (*_count)++;
    }
    return *this; // allow chaining
  }

  // Move assignement operator
  my_shared_ptr<T> &operator=(my_shared_ptr<T> &&rhs) {
    if (this != &rhs) {
      this->reset();
      _ptr = rhs._ptr;
      _count = rhs._count;
      rhs._ptr = nullptr;
      rhs._count = nullptr;
    }
    return *this; // allow chaining
  }

  ~my_shared_ptr() { this->reset(); }

  // Overload operator*
  T &operator*() const { return *_ptr; }

  // Overload operator->
  T *operator->() const { return _ptr; }

  // Access operator
  T &operator[](size_t idx) const { return _ptr[idx]; }

  // Get the raw pointer
  T *get() const { return _ptr; }

  // Get count
  size_t get_count() const {
    if (_count != nullptr)
      return *_count;
    return 0;
  }

  // Explicit move operations from a raw pointer
  // Initialize from a raw pointer
  my_shared_ptr(T *ptr) : _ptr(ptr), _count(new size_t(1)){};

  // Move assignement operator from raw using copy-and-swap idiom
  my_shared_ptr &operator=(const T *&&ptr) {
    this->reset();
    _ptr = ptr;
    _count = new size_t(1);
    ptr = nullptr;
  };

  my_shared_ptr &operator=(const T *ptr) = delete;
};
