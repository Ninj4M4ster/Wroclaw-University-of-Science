# author: Jakub Drzewiecki 268418

function forward(v, u, t)
    sum = t(0)
    for i = eachindex(v)
        sum += v[i] * u[i]
    end
    return sum
end

function backwards(v, u, t)
    sum = t(0)
    for i = eachindex(v)
        sum += v[length(v) - i + 1] * u[length(u) - i + 1]
    end
    return sum
end

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


t = Float64
x = [t(2.718281828), t(-3.141592654), t(1.414213562), t(0.5772156649), t(0.3010299957)]
y = [t(1486.2497), t(878366.9879), t(-22.37492), t(4773714.647), t(0.000185049)]

ascending(x, y, t)