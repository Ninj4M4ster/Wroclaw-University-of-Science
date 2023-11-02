# author: Jakub Drzewiecki 268418

import Pkg
Pkg.add("Plots")
using Plots

# Recursive function
# curr_x - current value of X
# c - parameter
function f(curr_x, c)
    return Float64(curr_x) * Float64(curr_x) + Float64(c)
end

# This function iterates 40 times, calculating and saving values of given function.
# set - pair of values: c parameter and x start value
# fun - function
function iterate(set, fun)
    result = []
    result = append!(result, set[2])
    current_val = set[2]
    c = set[1]
    for i = 1:40
        current_val = fun(current_val, c)
        result = append!(result, current_val)
    end
    return result
end

# Main function
function main()
    # sets of values: (c, x_0)
    set = [[-2.0, 1.0],
            [-2.0, 2.0],
            [-2.0, 1.99999999999999],
            [-1.0, 1.0],
            [-1.0, -1.0],
            [-1.0, 0.75],
            [-1.0, 0.25]]

    # Generate results for all sets
    result = []
    for i = 1:7
        result = append!(result, [iterate(set[i], f)])
    end

    # Print results
    for i = 1:41
        print("i = ", i - 1)
        for j = 1:7
            print(", x", j ," = ", result[j][i])
        end
        println()
    end

    # Make plots
    for i = 1:7
        display(plot(result[i]))
    end
end

main()