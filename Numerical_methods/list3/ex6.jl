# author: Jakub Drzewiecki 268418

include("methods.jl")

function main()
    f1 = x -> exp(1.0 - x) - 1
    pf1 = x -> -exp(1.0 - x)
    f2 = x -> x * exp(-x)
    pf2 = x -> - (x - 1) * exp(-x)
    acc = 10.0^(-5)
    results_f1_1 = mbisekcji(f1, -5.0, 5.0, acc, acc)
    results_f1_2 = mstycznych(f1, pf1, 0.0, acc, acc, 100)
    results_f1_3 = msiecznych(f1, -1.0, 0.0, acc, acc, 100)
    results_f2_1 = mbisekcji(f2, -0.5, 0.5, acc, acc)
    results_f2_2 = mstycznych(f2, pf2, -1.0, acc, acc, 100)
    results_f2_3 = msiecznych(f2, -3.0, -5.0, acc, acc, 100)
    println("F1:")
    println("Metoda bisekcji: " , results_f1_1)
    println("Metoda Newtona: ", results_f1_2)
    println("Metoda siecznych: ", results_f1_3)
    println("F2:")
    println("Metoda bisekcji: " , results_f2_1)
    println("Metoda Newtona: ", results_f2_2)
    println("Metoda siecznych: ", results_f2_3)
    println("Test - f1, x0 > 1")
    for i = 1:20
        x0 = Float64(i)
        results_f1_2 = mstycznych(f1, pf1, x0, acc, acc, 100)
        println("x0 = ", x0, ", wynik: ", results_f1_2)
    end
    println("Test - f2, x0 > 1")
    for i = 1:20
        x0 = Float64(i)
        results_f2_2 = mstycznych(f2, pf2, x0, acc, acc, 100)
        println("x0 = ", x0, ", wynik: ", results_f2_2)
    end
    println("Test - f2, x0=1")
    results_f2_2 = mstycznych(f2, pf2, 1.0, acc, acc, 100)
    println("x0 = 1, wynik: ", results_f2_2)
end

main()