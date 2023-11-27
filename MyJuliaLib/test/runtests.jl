using MyJuliaLib
using Test

@testset "MyJuliaLib.jl" begin
    # Write your tests here.
    test_trapz_request = trapz_request(x -> 3*x^2, 1., 2., 100)
    @test MyJuliaLib.isapprox(MyJuliaLib.trapezoid(test_trapz_request), trapz_result(7., 0.))
end
