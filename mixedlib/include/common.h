#pragma once
#include "julia.h"
#include <iostream>

struct IntegResult { // interface should be kept in sync with julie.jl
  double I;
  double err;
};

struct IntegRequest {
  int64_t n;
  double a;
  double b;
  double *data; // csting of function to integrate
};

inline jl_value_t *box_request(IntegRequest *req) {
  // format string to pass to jl_eval_string
  const char *req_cstr_template =
      "trapz_request(%f, %f, Array{Float64,1}(undef, %d))";
  char buffer[256];
  std::snprintf(buffer, 256, req_cstr_template, req->a, req->b, req->n);
  jl_value_t *req_boxed = jl_eval_string(buffer);
  jl_array_t *data = (jl_array_t *)jl_get_nth_field(req_boxed, 2);
  double *xData = (double *)jl_array_data(data);
  for (int i = 0; i < req->n; i++) {
    xData[i] = req->data[i];
  }
  return req_boxed;
}

inline IntegResult *unbox_result(jl_value_t *res) {
  IntegResult *IVal = new IntegResult();
  jl_value_t *I = jl_get_nth_field(res, 0);
  jl_value_t *err = jl_get_nth_field(res, 1);
  IVal->I = jl_unbox_float64(I);
  IVal->err = jl_unbox_float64(err);
  return IVal;
}
