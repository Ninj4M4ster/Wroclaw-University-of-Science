# author: Jakub Drzewiecki 268418

include("methods.jl")
using .Methods

function main()
    f_1 = x -> exp(x)
    f_2 = x -> x^2 * sin(x)
    n = [5, 10, 15]
    for i = eachindex(n)
        rysujNnfx(f_1, 0.0, 1.0, n[i])
    end

    for i = eachindex(n)
        rysujNnfx(f_2, -1.0, 1.0, n[i])
    end
end

main()
