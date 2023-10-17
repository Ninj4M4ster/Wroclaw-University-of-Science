# author: Jakub Drzewiecki 268418

function f(x)
    return sin(x) + cos(Float64(3.0) * x)
end

function f_prim(x)
    return cos(x) - Float64(3) * sin(Float64(3) * x)
end

function main() 
    x = Float64(1)
    result = f_prim(x)
    println("Dokladna wartosc pochodnej: ", result)
    for i = 0:54
        h = Float64(2) ^ (-i)
        derivative = (f(x + h) - f(x)) / h
        println("i = ", i, ", wartosc pochodnej: ", derivative, ", 1 + h: ", 1.0 + h, ", roznica: ", abs(result - derivative))
    end
end

main()