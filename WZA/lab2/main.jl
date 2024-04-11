function divWithRest(x::Vector{Float64}, y::Vector{Float64})
    if(length(x) < length(y))
        return 0
    end
    i = length(x)
    j = length(y)
    result = zeros(i-j + 1)
    reminder = x
    while(j >= 0)
        res = x[i] / y[length(y)]
        result[j + 1] = res
        y_temp = copy(y)
        for k = eachindex(y_temp)
            y_temp[k] = y_temp[k] * res
        end
        for k = eachindex(y_temp)
            reminder[i - length(y_temp) + k] -= y_temp[k]
        end
        x = reminder
        i-=1
        j-=1
    end
    return result, reminder
end

a = [-12.0, -4.0, 3.0, 1.0]
b = [-4.0, 1.0]

println(divWithRest(a, b))