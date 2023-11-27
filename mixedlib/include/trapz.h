#pragma once
#include "common.h"
#include "julia.h"
#include <iostream>
#include <stdio.h>

namespace mymemory {
class JuliaTrapzRequest {
public:
  JuliaTrapzRequest(double a, double b, int64_t n, double *data);
  ~JuliaTrapzRequest();

  jl_value_t *boxed_request();
  double get_result();
  bool mem_check();

private:
  jl_value_t *req_boxed;
  jl_array_t *data;
  jl_value_t *result;
  jl_function_t *trapz_func;
}; // class JuliaTrapzRequest
} // namespace mymemory
