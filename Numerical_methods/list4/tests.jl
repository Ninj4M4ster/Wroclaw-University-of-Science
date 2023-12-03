# author: Jakub Drzewiecki 268418

import Pkg
Pkg.add("Test")
using Test

include("methods.jl")
using .Methods

"""
Test - wielomian
"""
function test1()
    x = [1.0, 2.0, 3.0, 4.0, 5.0]
    f = x -> 3x^3 - 2x^2 + 4x - 12
    y = f.(x)
    ilorazy = ilorazyRoznicowe(x, y)
    war = t -> warNewton(x, ilorazy, t)
    @test ilorazy == [-7.0, 19.0, 16.0, 3.0, 0.0]
    @test naturalna(x, ilorazy) == [-12.0, 4.0, -2.0, 3.0, 0.0]
    @test war.(x) == y
end

"""
Test - zadanie 4 z listy 4 z cwiczen.
"""
function test2()
    x = [-2.0, -1.0, 0.0, 1.0, 2.0, 3.0]
    y = [-25.0, 3.0, 1.0, -1.0, 27.0, 235.0]
    ilorazy = ilorazyRoznicowe(x, y)
    war = t -> warNewton(x, ilorazy, t)
    @test ilorazy == [-25.0, 28.0, -15.0, 5.0, 0.0, 1.0]
    @test naturalna(x, ilorazy) == [1.0, -3.0, 0.0, 0.0, 0.0, 1.0]
    @test war.(x) == y
end

function main()
    test1()
    test2()
end

main()