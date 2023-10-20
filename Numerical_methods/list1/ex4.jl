# author: Jakub Drzewiecki 268418

# Find such number x so that 1 < x < 2 and x*(1/x) != 1
function find_x()
    x = Float64(1)
    one = Float64(1)
    while(nextfloat(x) * (one / nextfloat(x)) == one && x < Float64(2))
        x = nextfloat(x)
    end
    return nextfloat(x)
end

# Find the lowest value x so that x*(1/x) != 1
function find_lowest_x()
    x = Float64(0)
    one = Float64(1)
    while(nextfloat(x) * (one / nextfloat(x)) == one)
        x = nextfloat(x)
    end
    return nextfloat(x)
end

function main()
    println("1 < x < 2")
    println(find_x())
    println("Lowest possible x")
    println(find_lowest_x())
end

main()
