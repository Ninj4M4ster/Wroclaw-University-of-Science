# author: Jakub Drzewiecki 268418

import Pkg
Pkg.add("Plots")
using Plots

# Calculate value of function e^x ln(1 + e^(-x))
function f(x::Float64)
    return exp(x) * log1p(exp(-x))
end

# Generate plot for given function
# Fun - function to visualize
function generate_plot(fun)
    plot(fun, -60, 60, label="exp(x)ln(1+exp(-x))")
end

# Main function
function main()
    generate_plot(f)
end

main()