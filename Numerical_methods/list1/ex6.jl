# author: Jakub Drzewiecki 268418

function f(x)
    return sqrt(x^2 + 1) - 1
end

function g(x)
    return x^2 / (sqrt(x^2 + 1) + 1)
end

function main()
    num = Float64(1) / Float64(8)
    i = 1
    while(i < 200)
        println("i : ", i ,", f(x) = ", f(num), ", g(x) = ", g(num))
        num /= Float64(8)
        i+=1
    end
end

main()