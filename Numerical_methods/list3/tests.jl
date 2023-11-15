# author: Jakub Drzewiecki 268418

import Pkg
Pkg.add("Test")
using Test

include("methods.jl")

function test_bisect()
    @test mbisekcji(x -> x^2-2, -1.0, 5.0, 10^(-2), 10^(-2))[1] == 1.4140625
    @test mbisekcji(x -> x^2-2, -1.0, 1.0, 10^(-2), 10^(-2))[4] == 1
    println("Bisect passed tests")
end

function test_tangent()
    @test mstycznych(x -> log(x)*x, x -> log(x)+1, 2.0, 10^(-2), 10^(-2), 100)[1] == 1.0000774890317474
    @test mstycznych(x -> log(x)*x, x -> log(x)+1, 0.5, 10^(-2), 10^(-2), 100)[1] == 1.0038833183795772
    println("Tangent passed tests")
end

function test_secant()
    @test msiecznych(x -> exp(-x) * x^2 - 0.2, 0.2, 0.4, 10^(-2), 10^(-2), 100)[1] == 0.6046384102560074
    @test msiecznych(x -> exp(-x) * x^2 - 0.2, 2.0, 2.5, 10^(-2), 10^(-2), 100)[1] == 4.720287127669367
    @test msiecznych(x -> exp(-x) * x^2 - 0.2, -2.0, -1.0, 10^(-2), 10^(-2), 100)[1] == -0.372969642131026
    println("Secant passed tests")
end

function main()
    test_bisect()
    test_tangent()
    test_secant()
end

main()