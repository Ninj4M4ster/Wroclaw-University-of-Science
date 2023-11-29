# author: Jakub Drzewiecki 268418

import Pkg
Pkg.add("Test")
using Test

include("methods.jl")
using .Methods

function main()
    x = [3.0, 1.0, 5.0, 6.0]
    f = [1.0, -3.0, 2.0, 4.0]
    ilorazy = ilorazyRoznicowe(x, f)
    fun = t -> warNewton(x, ilorazy, t)
    f = x -> -x^6 + 4x^5 - 2x^4 + 4x^3 - 3x^2 + 8x - 5
    rysujNnfx(f, -5.0, 5.0, 2)
end

main()