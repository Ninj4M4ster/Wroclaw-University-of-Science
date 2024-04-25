
function divWithRest(x, y)
    if(length(x) < length(y))
        return [0.0]
    end
    i = length(x)
    j = length(y)
    result = zeros(i-j + 1)
    t = i - j + 1
    reminder = x
    while(t > 0 && reminder[1] != 0.0 && length(reminder) >= length(y))
        res = x[i] / y[length(y)]
        result[t] = res
        y_temp = copy(y)
        for k = eachindex(y_temp)
            y_temp[k] = y_temp[k] * res
        end
        for k = eachindex(y_temp)
            reminder[i - length(y_temp) + k] -= y_temp[k]
        end
        if(reminder[length(reminder)] == 0.0)
            new_reminder = Vector{Float64}()
            for index = 1:length(reminder) - 1
                append!(new_reminder, reminder[index])
            end
            reminder = new_reminder
        end
        if(length(reminder) == 0)
            append!(reminder, 0.0)
        end
        x = reminder
        i-=1
        j-=1
        t -= 1
    end
    return result, reminder
end

function multiply(x, y)
    i = length(x)
    j = length(y)

    result = zeros(Float64, i + j - 1)
    for i = eachindex(x)
        for j = eachindex(y)
            result[i+j-1] += x[i] * y[j]
        end
    end
    k = length(result)
    while k > 1 && result[k] == 0.0
        pop!(result)
        k-=1
    end
    return result
end

function subtract(x, y)
    i = length(x)
    j = length(y)
    k = 1
    result = Vector{Float64}()
    while k <= i && k <= j
        tmp = x[k] - y[k]
        append!(result, tmp)
        k+=1
    end
    if j > i
        while k <= j
            append!(result, -y[k])
            k += 1
        end
    else
        while k <= i
            append!(result, x[k])
            k += 1
        end
    end
    return result
end

function nwd(a, b)
    while b[1] != 0.0
        div_res, div_rem = divWithRest(a, b)
        a, b = b, div_rem
    end
    return a
end

function euclides(a, b)
    x = [1.0]
    y = [0.0]
    if(b[1] != 0.0)
        div_res, div_reminder = divWithRest(a, b)
        x, y = euclides(b, div_reminder)
        pom = y
        y = subtract(x, multiply(div_res, y))
        x = pom
    end
    
    return x, y
end

function main()
    a = [2.0, 5.0, 3.0, 2.0]
    b = [1.0, 2.0]
    # multiply(a, b)
    # divWithRest(a, b)
    # subtract(a, b)
    println("A, B")
    println(euclides(copy(a), copy(b)))
    println("nwd")
    println(nwd(a, b))
end

main()