# author: Jakub Drzewiecki 268418

# Forward computation of scalar product
# v - first vector
# u - second vector
# t - Type, either Float16, Float32 or Float 64
function forward(v, u, t)
    sum = t(0)
    for i = eachindex(v)
        sum += v[i] * u[i]
    end
    return sum
end

# Backward computation of scalar product
# v - first vector
# u - second vector
# t - Type, either Float16, Float32 or Float 64
function backwards(v, u, t)
    sum = t(0)
    for i = eachindex(v)
        sum += v[length(v) - i + 1] * u[length(u) - i + 1]
    end
    return sum
end

# Scalar product. After multiplying, all values greater than 0 are sorted descending and then summed up.
# Values lesser than 0 are sorted ascending and also summed up.
# Finally, the two remaining values are added and returned.
# v - first vector
# u - second vector
# t - Type, either Float16, Float32 or Float 64
function descending(v, u, t)
    plus_array = []
    minus_array = []
    for i = eachindex(v)
        temp_sum = v[i] * u[i]
        if temp_sum >= 0
            push!(plus_array, temp_sum)
        else
            push!(minus_array, temp_sum)
        end
    end
    plus_array = sort(plus_array, rev=true)
    minus_array = sort(minus_array)

    plus_sum = t(0)
    minus_sum = t(0)
    for i = eachindex(plus_array)
        plus_sum += plus_array[i]
    end
    for i = eachindex(minus_array)
        minus_sum += minus_array[i]
    end

    return plus_sum + minus_sum
end

# Scalar product. After multiplying, all values greater than 0 are sorted ascending and then summed up.
# Values lesser than 0 are sorted descending and also summed up.
# Finally, the two remaining values are added and returned.
# v - first vector
# u - second vector
# t - Type, either Float16, Float32 or Float 64
function ascending(u, v, t)
    plus_array = []
    minus_array = []
    for i = eachindex(v)
        temp_sum = v[i] * u[i]
        if temp_sum >= 0
            push!(plus_array, temp_sum)
        else
            push!(minus_array, temp_sum)
        end
    end
    plus_array = sort(plus_array)
    minus_array = sort(minus_array, rev=true)

    plus_sum = t(0)
    minus_sum = t(0)
    for i = eachindex(plus_array)
        plus_sum += plus_array[i]
    end
    for i = eachindex(minus_array)
        minus_sum += minus_array[i]
    end

    return plus_sum + minus_sum
end

# Main function, show result using all methods
function main()
    for t in [Float32,Float64]
        x_a = [t(2.718281828), t(-3.141592654), t(1.414213562), t(0.5772156649), t(0.3010299957)]
        y_a = [t(1486.2497), t(878366.9879), t(-22.37492), t(4773714.647), t(0.000185049)]
        x_b = [t(2.718281828), t(-3.141592654), t(1.414213562), t(0.577215664), t(0.301029995)]
        y_b = [t(1486.2497), t(878366.9879), t(-22.37492), t(4773714.647), t(0.000185049)]

        println(t)
        println("Original vectors")
        println("a: ", forward(x_a, y_a, t))
        println("b: ", backwards(x_a, y_a, t))
        println("c: ", descending(x_a, y_a, t))
        println("d: ", ascending(x_a, y_a, t))
        println("Deranged vectors")
        println("a: ", forward(x_b, y_b, t))
        println("b: ", backwards(x_b, y_b, t))
        println("c: ", descending(x_b, y_b, t))
        println("d: ", ascending(x_b, y_b, t))
        println()
    end
end

main()