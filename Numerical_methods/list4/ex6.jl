# author: Jakub Drzewiecki 268418

include("methods.jl")
using .Methods

function main()
    f_1 = x -> abs(x)
    f_2 = x -> 1.0 / (1.0 + x^2)
    n = [5, 10, 15]
    for i = eachindex(n)
        rysujNnfx(f_1, -1.0, 1.0, n[i])
    end

    for i = eachindex(n)
        rysujNnfx(f_2, -5.0, 5.0, n[i])
    end
end

main()
