#include "trapz.h"
#include <thread>

#include "gtest/gtest.h"

// Define max size for a double array is 2^32 - 1
// (see https://docs.julialang.org/en/v1/manual/arrays/#man-array-creation)

// Define a test fixture class
class TrapzStressTest : public testing::TestWithParam<std::size_t> {};

// Define the parameter values using the INSTANTIATE_TEST_SUITE_P macro
INSTANTIATE_TEST_SUITE_P(Params, TrapzStressTest,
                         testing::Values(100000, 1000000, 100000000));

TEST_P(TrapzStressTest, WillFail) { // this test should Fail
  // Import the module
  std::size_t size = GetParam();
  std::cout << "allocated " << size << " elements" << std::endl;
  double *data = new double[size];
  for (int i = 0; i < size; i++) {
    double x = (double)i / (double)size;
    data[i] = x * x;
  }
  std::cout << "allocating" << std::endl;
  auto req = new mymemory::JuliaTrapzRequest(0.0, 1.0, size, data);
  std::cout << "allocated" << std::endl;

  ASSERT_TRUE(req->mem_check());
  std::cout << "mem checked" << std::endl;
  EXPECT_NEAR(req->get_result(), 0.3333333333333333, 0.05);

  // EXPECT_NEAR(req->get_result(), 0.3333333333333333, 0.05);
  //  call some random function to trigger garbage collection
  jl_eval_string("using GC");
  jl_eval_string("GC.gc()");

  // wait for 1 second
  std::this_thread::sleep_for(std::chrono::seconds(1));

  // expect result to be close to 1 /3
  ASSERT_TRUE(req->mem_check());
  EXPECT_NEAR(req->get_result(), 0.3333333333333333, 0.05);
}
