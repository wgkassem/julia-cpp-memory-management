#include "common.h"

#include "gtest/gtest.h"

JULIA_DEFINE_FAST_TLS

TEST(Common, CanCallSqrt) {
  jl_init();
  jl_function_t *sqrt = jl_get_function(jl_base_module, "sqrt");
  jl_value_t *ret = jl_call1(sqrt, jl_box_float64(2.0));
  double ret_unboxed = jl_unbox_float64(ret);
  EXPECT_EQ(ret_unboxed, 1.4142135623730951);
  jl_atexit_hook(0);
}

TEST(Common, CanImportMyJuliaLib) {
  jl_init();
  jl_eval_string("using .MyJuliaLib");
  jl_module_t *mod = (jl_module_t *)jl_eval_string("import MyJuliaLib");
  // Assert that the module exists
  ASSERT_NE(mod, nullptr);
  jl_atexit_hook(0);
}

TEST(Common, CanAllocateIntegRequest) {
  jl_init();
  // Import the module
  jl_eval_string("using MyJuliaLib");
  // Assert that the function exists
  IntegRequest *req = new IntegRequest();
  req->n = 100;
  req->a = 0.0;
  req->b = 1.0;
  req->data = new double[req->n];

  // create x array, from 0 to 1 with 100 points
  double x[req->n];
  for (int i = 0; i < req->n; i++) {
    x[i] = (double)i / (double)req->n;
    req->data[i] = x[i] * x[i];
  }
  jl_value_t *trp_req = box_request(req);

  JL_GC_PUSH1(&trp_req);
  ASSERT_NE(trp_req, nullptr);
  // Get size of struct
  size_t size = jl_datatype_size(jl_typeof(trp_req));
  // Assert thet the size is correct
  ASSERT_GT(size, 0);

  // Get pointer to stored values
  jl_value_t *lower = jl_get_nth_field(trp_req, 0);
  jl_value_t *upper = jl_get_nth_field(trp_req, 1);
  jl_array_t *data = (jl_array_t *)jl_get_nth_field(trp_req, 2);
  jl_function_t *length = jl_get_function(jl_main_module, "length");
  jl_value_t *n = jl_call1(length, (jl_value_t *)data);
  double *xData = (double *)jl_array_data(data);

  // Assert that the types are correct
  ASSERT_TRUE(jl_typeis(n, jl_int64_type));
  EXPECT_EQ(jl_unbox_int64(n), req->n);

  ASSERT_TRUE(jl_typeis(lower, jl_float64_type));
  EXPECT_EQ(jl_unbox_float64(lower), req->a);

  ASSERT_TRUE(jl_typeis(upper, jl_float64_type));
  EXPECT_EQ(jl_unbox_float64(upper), req->b);

  for (int i = 0; i < req->n; i++) {
    ASSERT_EQ(xData[i], req->data[i]);
  }

  JL_GC_POP();
  jl_atexit_hook(0);

  delete req->data;
}

TEST(Common, CanCallMyJuliaLibTrapz) {
  jl_init();
  jl_eval_string("using MyJuliaLib");
  jl_eval_string("using GC");
  // get trapezoid function
  jl_function_t *trapezoid = jl_get_function(jl_main_module, "trapezoid");
  // Create a trapzoid_request struct to pass to Julia
  IntegRequest *req = new IntegRequest();
  req->a = 0.0;
  req->b = 1.0;
  req->n = 100;
  req->data = new double[req->n];
  // create x array, from 0 to 1 with 100 points
  double x[req->n];
  for (int i = 0; i < req->n; i++) {
    x[i] = (double)i / (double)req->n;
    req->data[i] = x[i] * x[i];
  }

  // Convert the request struct to a Julia struct
  jl_value_t *req_boxed = box_request(req);
  JL_GC_PUSH1(&req_boxed);
  ASSERT_NE(req_boxed, nullptr);

  jl_eval_string("GC.gc()");

  // Call trapezoid with the req struct and get back a result struct
  jl_value_t *res = jl_call1(trapezoid, req_boxed);
  ASSERT_NE(res, nullptr);
  IntegResult *IVal = unbox_result(res);

  jl_eval_string("GC.gc()");

  // Assert that the result is almost 1/3
  EXPECT_NEAR(IVal->I, 1.0 / 3.0, 5e-2);

  // JL_GC_POP();
  jl_atexit_hook(0);
  delete req->data;
}
