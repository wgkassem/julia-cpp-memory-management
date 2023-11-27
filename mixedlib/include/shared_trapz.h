#pragma once
#include "common.h"
#include "julia.h"
#include "mymemory/greedy_shared_ptr.h"

namespace mymemory {
class JuliaSharedTrapzRequest {
public:
  JuliaSharedTrapzRequest(double a, double b, int64_t n, double *data);
  ~JuliaSharedTrapzRequest();

  jl_value_t *boxed_request();

private:
  IntegRequest *req;
  mymemory::greedy_shared_ptr<jl_value_t> req_boxed;
  mymemory::greedy_shared_ptr<jl_array_t> data;
}; // class JuliaTrapzRequest
} // namespace mymemory
