# author: Jakub Drzewiecki 268418

import Pkg
Pkg.add("Polynomials")
using Polynomials

# Normal wilkinson
wilkinson=Polynomial(reverse([1.0, -210.0, 20615.0,-1256850.0,
    53327946.0,-1672280820.0, 40171771630.0, -756111184500.0,          
    11310276995381.0, -135585182899530.0,
    1307535010540395.0,     -10142299865511450.0,
    63030812099294896.0,     -311333643161390640.0,
    1206647803780373360.0,     -3599979517947607200.0,
    8037811822645051776.0,      -12870931245150988800.0,
    13803759753640704000.0,      -8752948036761600000.0,
    2432902008176640000.0]))

# Disrupted wilkinson
wilkinson_b=Polynomial(reverse([1.0, (-210.0 - (2.0 ^ -23)), 20615.0,-1256850.0,
    53327946.0,-1672280820.0, 40171771630.0, -756111184500.0,          
    11310276995381.0, -135585182899530.0,
    1307535010540395.0,     -10142299865511450.0,
    63030812099294896.0,     -311333643161390640.0,
    1206647803780373360.0,     -3599979517947607200.0,
    8037811822645051776.0,      -12870931245150988800.0,
    13803759753640704000.0,      -8752948036761600000.0,
    2432902008176640000.0]))

# Calculate absolute value of normal wilkinson in natural form
# x - function argument
function P(x::Float64)
    return abs(wilkinson(x))
end

# Calculate absolute value of disrupted wilkinson in natural form
# x - function argument
function P(x::ComplexF64)
    return abs(wilkinson_b(x))
end

# Calculate absolute value of normal wilkinson
function p(x::Float64)
    return abs((x - 20.0) * (x - 19.0) * (x - 18.0) * (x - 17.0) * (x - 16.0) * (x - 15.0) * (x - 14.0) * (x - 13.0) * (x - 12.0) * (x - 11.0) * (x - 10.0) * 
    (x - 9.0) * (x - 8.0) * (x - 7.0) * (x - 6.0) * (x - 5.0) * (x - 4.0) * (x - 3.0) * (x - 2.0) * (x - 1.0))
end

# Main function
function main()
    n = 20
    x = roots(wilkinson)
    println(x)
    println("a)")
    for i = 1:n
        println("K = ", i)
        println("Zk = ", x[i])
        println("|P(Zk)| = ", P(x[i]))
        println("|p(Zk)| = ", p(x[i]))
        println("|Zk - k| = ", abs(x[i] - i))
        println()
    end
    x = roots(wilkinson_b)
    println("b)")
    for i = 1:n
        println("K = ", i)
        println("Zk = ", x[i])
        println("|P(Zk)| = ", P(x[i]))
        println()
    end
end

main()