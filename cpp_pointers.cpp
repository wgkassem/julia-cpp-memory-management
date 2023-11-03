#include <iostream>
#include <memory>

#include "greedy_shared_ptr.h"

struct A {
  int val;
  A(int a) : val(a) {}
  ~A() {}
};

A *foo() {
  A *a = new A(10);
  std::cout << "Creating a new A object with value 10" << std::endl;
  return a;
}

void bar(A *a) { delete a; }

void baz(A *a) {
  greedy_shared_ptr<A> p(std::move(a));
  std::cout << "Number of pointers to A: " << p.get_count() << std::endl;
}

int main() {

  // Create a shared pointer to an A object
  my_shared_ptr<A> p(new A(11)); // constructor
  // Create a shared point to an A object that is not initialized
  std::cout << "Constructor:\t\t Number of pointers to A: " << p.get_count()
            << std::endl; // 1

  // Call copy constructor to p
  my_shared_ptr<A> p_copy(p); // copy constructor
  std::cout << "Copy-constructor:\t Number of pointers to A: " << p.get_count()
            << std::endl; // 2

  // Copy assignment operator to p with p_null
  my_shared_ptr<A> p_null = p; // default constructor
  std::cout << "Copy-assignment:\t Number of pointers to A: "
            << p_copy.get_count() << std::endl; // 3
  // Move constructor to p_move from p_null
  my_shared_ptr<A> p_move(std::move(p_null)); // move constructor
  std::cout << "Move-constructor:\t Number of pointers to A: " << p.get_count()
            << " "
            << "p_null is: " << p_null.get() << std::endl; // nullptr

  // Move using move assignment operator to p_move_again from p_move
  my_shared_ptr<A> p_move_again;
  p_move_again = std::move(p_move); // move assignment operator
  std::cout << "Move-assignemnt:\t Number of pointers to A: " << p.get_count()
            << ", p_move is nullptr: " << p_move.get() << std::endl; // nullptr

  // Release the resource from p_move
  p_move_again.reset();
  std::cout << "Reset 1:\t\t Number of pointers to A: " << p.get_count()
            << std::endl; // 2
  // Release all resources from p
  p.reset();
  p_copy.reset();
  std::cout << "Reset all:\t\t Number of pointers to A: " << p.get_count()
            << std::endl; // 0

  //////////////////////////////
  // Test out greedy_shared_ptr
  // //////////////////////////

  std::cout << "//////////////////////////////" << std::endl;
  std::cout << "// Test out greedy_shared_ptr" << std::endl;
  std::cout << "//////////////////////////////" << std::endl;

  A *tmp2 = new A(11); // Create a raw pointer to an A object
  greedy_shared_ptr<A> p0(std::move(tmp2)); // move constructor
  std::cout << "Explicit Move Contructor: Number of pointers to A: "
            << p0.get_count() << ", original pointer is null: " << tmp2
            << std::endl; // 1, nullptr

  // Create a shared pointer
  A *tmp_ptr = new A(10);
  greedy_shared_ptr<A> p1;
  p1 = std::move(tmp_ptr);
  std::cout << "Explicit Move assignment: Number of pointers to A: "
            << p1.get_count() << ", original pointer is null: " << tmp_ptr
            << std::endl; // 1, nullptr

  // A *tmp3 = new A(11); // Create a raw pointer to an A object
  // greedy_shared_ptr<A> p2(tmp3); // illegal, constructor excepts rvalue

  greedy_shared_ptr<A> p3(new A(11));
  std::cout << "Constructor: Number of pointers to A: " << p3.get_count()
            << std::endl; // 1

  // IMplicit move assignment operator
  greedy_shared_ptr<A> p4 = foo();
  std::cout << "Implicit Move assignment: Number of pointers to A: "
            << p4.get_count() << " value of managed object is " << p4->val
            << std::endl; // 1

  return 0;
}
