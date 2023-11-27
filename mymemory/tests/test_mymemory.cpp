#include <memory>

#include "gtest/gtest.h"

#include "mymemory/greedy_shared_ptr.h"

struct A {
  int val;
  A(int a) : val(a) {}
  ~A() {}
};

A *foo() {
  A *a = new A(10);
  return a;
}

void bar(A *a) { delete a; }

void baz(A *a) {
  mymemory::greedy_shared_ptr<A> p(std::move(a));
  std::cout << "Number of pointers to A: " << p.get_count() << std::endl;
}

TEST(MyMemory, MySharedPointers) {
  // Create a shared pointer to an A object
  mymemory::my_shared_ptr<A> p(new A(11)); // constructor
  // Create a shared point to an A object that is not initialized
  ASSERT_EQ(p.get_count(), 1);
  ASSERT_NE(p, nullptr); // p is not nullptr

  // Call copy constructor to p
  mymemory::my_shared_ptr<A> p_copy(p); // copy constructor
  // assert that the count is 2
  ASSERT_EQ(p.get_count(), 2);
  ASSERT_NE(p, nullptr); // p is not nullptr

  // Copy assignment operator to p with p_null
  mymemory::my_shared_ptr<A> p_null = p; // default constructor
  // assert that the count is 3
  ASSERT_EQ(p.get_count(), 3);

  // Move constructor to p_move from p_null
  mymemory::my_shared_ptr<A> p_move(std::move(p_null)); // move constructor
  // assert that the count is still 3
  ASSERT_EQ(p.get_count(), 3);
  ASSERT_EQ(p_null, nullptr); // p_null is nullptr

  // Move using move assignment operator to p_move_again from p_move
  mymemory::my_shared_ptr<A> p_move_again;
  p_move_again = std::move(p_move); // move assignment operator
  ASSERT_EQ(p_move, nullptr);       // p_move is nullptr
  ASSERT_EQ(p_move_again.get_count(), 3);

  // Release the resource from p_move
  p_move_again.reset();
  p.reset();
  p_copy.reset();
  ASSERT_EQ(p.get_count(), 0);
}

TEST(MyMemory, GreedySharedPtr) {
  //////////////////////////////
  // Test out mymemory::greedy_shared_ptr
  // //////////////////////////

  A *tmp2 = new A(11); // Create a raw pointer to an A object
  mymemory::greedy_shared_ptr<A> p0(std::move(tmp2)); // move constructor
  std::cout << "Explicit Move Contructor: Number of pointers to A: "
            << p0.get_count() << ", original pointer is null: " << tmp2
            << std::endl; // 1, nullptr

  // Create a shared pointer
  A *tmp_ptr = new A(10);
  mymemory::greedy_shared_ptr<A> p1;
  p1 = std::move(tmp_ptr);
  std::cout << "Explicit Move assignment: Number of pointers to A: "
            << p1.get_count() << ", original pointer is null: " << tmp_ptr
            << std::endl; // 1, nullptr

  // A *tmp3 = new A(11); // Create a raw pointer to an A object
  // mymemory::greedy_shared_ptr<A> p2(tmp3); // illegal, constructor excepts
  // rvalue

  mymemory::greedy_shared_ptr<A> p3(new A(11));
  std::cout << "Constructor: Number of pointers to A: " << p3.get_count()
            << std::endl; // 1

  // IMplicit move assignment operator
  mymemory::greedy_shared_ptr<A> p4 = foo();
  std::cout << "Implicit Move assignment: Number of pointers to A: "
            << p4.get_count() << " value of managed object is " << p4->val
            << std::endl; // 1
}
