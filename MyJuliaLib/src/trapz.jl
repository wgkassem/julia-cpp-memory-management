import Base.isapprox

mutable struct trapz_result
    I::Float64
    err::Float64
end

mutable struct trapz_request
    a::Float64
    b::Float64
    data::Array{Float64,1}
end

"""
  trapezoid(request::trapz_request_function) :: trapz_result

  Compute the integral of the function f(x) over the interval [a,b] using the
  trapezoidal rule with n subintervals.
  The function f(x) is given as a function pointer.
"""
function trapezoid(request::trapz_request) :: trapz_result
  res = trapz_result(0.0, 0.0)
  size = length(request.data)
  h = (request.b - request.a)/(size-1)
  res.I = 0.5*(request.data[1] + request.data[size-1])
  for i = 1:size-1
    res.I += request.data[i]
  end
  res.I *= h
  # calculate error using Richardson extrapolation
  res.err = 0
  return res   
end

"""
  isapprox(a, b)

  Returns true if a and b are approximately equal; within 10%.
"""
function isapprox(a::trapz_result, b::trapz_result) :: Bool
  return Base.isapprox(a.I, b.I, rtol=0.1) && Base.isapprox(a.err, b.err, rtol=0.1)
end

