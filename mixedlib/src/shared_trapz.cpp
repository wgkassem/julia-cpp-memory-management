
#include "shared_trapz.h"

mymemory::JuliaSharedTrapzRequest::JuliaSharedTrapzRequest(double a, double b,
                                                           int64_t n,
                                                           double *data) {
  auto req = new IntegRequest();
  req->a = a;
  req->b = b;
  req->n = n;
  req->data = new double[n];
  for (int i = 0; i < n; i++) {
    req->data[i] = data[i];
  }
  this->req = req;
  this->req_boxed = ::box_request(req);
  this->data = (jl_array_t *)jl_get_nth_field(req_boxed, 2);
}

mymemory::JuliaSharedTrapzRequest::~JuliaSharedTrapzRequest() {
  delete this->req->data;
  delete this->req;
}

jl_value_t *mymemory::JuliaSharedTrapzRequest::boxed_request() {
  return this->req_boxed;
}
