# author: Jakub Drzewiecki 268418

include("methods.jl")

function main()
    f = x -> exp(x) - 3x
    acc = 10.0^(-4)
    results = mbisekcji(f, 0.0, 1.0, acc, acc)
    results_2 = mbisekcji(f, 1.0, 2.0, acc, acc)
    println("Pierwszy pierwiastek: ", results)
    println("Drugi pierwiastek: ", results_2)
end

main()