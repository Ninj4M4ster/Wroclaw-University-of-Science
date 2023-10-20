# author: Jakub Drzewiecki 268418

# F function
# x - number, can be integer or float
function f(x)
    return sqrt(x^2 + 1) - 1
end

# G function
# x - number, can be integer or float
function g(x)
    return x^2 / (sqrt(x^2 + 1) + 1)
end

# Main function, it tests the results using two versions of the same mathematic function
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