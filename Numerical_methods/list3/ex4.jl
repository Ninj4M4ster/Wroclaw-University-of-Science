# author: Jakub Drzewiecki 268418

include("methods.jl")

function main()
    f = x -> sin(x) - (((1.0 / 2.0) * x) ^ 2)
    pf = x -> cos(x) - x/2.0
    acc =  (10.0^(-5)) * (1.0 / 2.0)
    results_1 = mbisekcji(f, 1.5, 2.0, acc, acc)
    results_2 = mstycznych(f, pf, 1.5, acc, acc, 100)
    results_3 = msiecznych(f, 1.0, 2.0, acc, acc, 100)

    println("Metoda bisekcji: " , results_1)
    println("Metoda Newtona: ", results_2)
    println("Metoda siecznych: ", results_3)
end

main()
