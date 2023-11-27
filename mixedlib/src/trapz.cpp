#include "trapz.h"

mymemory::JuliaTrapzRequest::JuliaTrapzRequest(double a, double b, int64_t n,
                                               double *data) {
  jl_init();
  jl_eval_string("using MyJuliaLib");
  auto req = new IntegRequest();
  req->a = a;
  req->b = b;
  req->n = n;
  req->data = new double[n];
  for (int i = 0; i < n; i++) {
    req->data[i] = data[i];
  }
  this->req_boxed = ::box_request(req);
  this->data = (jl_array_t *)jl_get_nth_field(this->req_boxed, 2);
  // Calculate the result
  this->trapz_func = jl_get_function(jl_main_module, "trapezoid");
  std::cout << "getting result with " << this->req_boxed << std::endl;
  this->get_result();
  JL_GC_PUSH1(&this->req_boxed);
}

mymemory::JuliaTrapzRequest::~JuliaTrapzRequest() {}

jl_value_t *mymemory::JuliaTrapzRequest::boxed_request() {
  return this->req_boxed;
}

double mymemory::JuliaTrapzRequest::get_result() {
  // call trapezoid and return the result

  if (this->result == nullptr) {
    this->result = jl_call1(this->trapz_func, this->req_boxed);
  }
  JL_GC_PUSH1(&this->result);
  return jl_unbox_float64(jl_get_nth_field(this->result, 0));
}

bool mymemory::JuliaTrapzRequest::mem_check() {
  // check if the memory is still valid
  // if not, return false

  return this->data != nullptr && this->req_boxed != nullptr &&
         this->result != nullptr;

  return true;
}
