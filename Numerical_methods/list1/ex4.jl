# author: Jakub Drzewiecki 268418

function find_x()
    x = Float64(1)
    one = Float64(1)
    while(nextfloat(x) * (one / nextfloat(x)) == one && x < Float64(2))
        x = nextfloat(x)
    end
    return nextfloat(x)
end

function find_lowest_x()
    x = Float64(0)
    one = Float64(1)
    while(nextfloat(x) * (one / nextfloat(x)) == one)
        x = nextfloat(x)
    end
    return nextfloat(x)
end

find_lowest_x()
