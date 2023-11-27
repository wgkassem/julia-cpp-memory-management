
#include "shared_trapz.h"

#include "gtest/gtest.h"

JULIA_DEFINE_FAST_TLS

TEST(JuliaSharedTrapzRequest, Fail) { // this test should Fail
  jl_init();
  double x[100];
  double data[100];
  for (int i = 0; i < 100; i++) {
    double x = (double)i / (double)100;
    data[i] = x * x;
  }
  auto req = new mymemory::JuliaSharedTrapzRequest(0.0, 1.0, 100, data);
  jl_value_t *trp_req = req->boxed_request();
  // call some random function to trigger garbage collection
  jl_eval_string("sqrt(2.0)");
  ASSERT_NE(trp_req, nullptr);
}
