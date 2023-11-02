# author: Jakub Drzewiecki 268418

# Next value of recursive function
# current_p - current value
# r - parameter
# type - value types, Float32 or Float64
function next_p(current_p, r, type)
    return type(current_p) + type(r) * type(current_p) * (type(1.0) - type(current_p))
end

# Main function, it tests the recursive function
function main()
    p_0 = 0.01
    r = 3.0
    println("1.")
    res = p_0
    println("Bez obciecia")
    for i = 1:40
        res = next_p(res, r, Float32)
        println("I = ", i, ", p_i = ", res)
    end
    res = p_0
    println("Z obcieciem")
    for i = 1:40
        res = next_p(res, r, Float32)
        if i == 10
            res = trunc(res, digits=3)
        end
        println("I = ", i, ", p_i = ", res)
    end

    println("\n2.")
    res = p_0
    println("Float64")
    for i = 1:40
        res = next_p(res, r, Float64)
        println("I = ", i, ", p_i = ", res)
    end
end

main()