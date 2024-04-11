import Base.+
import Base.-
import Base.*
import Base./

struct GaussNumber
    a::Int64
    b::Int64
end

(+)(x::GaussNumber, y::GaussNumber) = GaussNumber(x.a + y.a, x.b + y.b)

(-)(x::GaussNumber, y::GaussNumber) = GaussNumber(x.a - y.a, x.b - y.b)

(*)(x::GaussNumber, y::GaussNumber) = GaussNumber(floor(Int64, x.a * y.a - x.b * y.b), floor(Int64, x.a * y.b + x.b * y.a))

(/)(x::GaussNumber, y::GaussNumber) = GaussNumber(floor(Int64, (x.a * y.a + x.b * y.b) / (y.a * y.a + y.b * y.b)), floor(Int64, (x.b * y.a - x.a * y.b) / (y.a * y.a + y.b * y.b)))

function divWithRest(x::GaussNumber, y::GaussNumber)
    if(y.a == 0 && y.b == 0)
        error("Division by zero exception")
    end
    div_result = x / y
    rest = x - div_result * y
    return div_result, rest
end

function nwd(x::GaussNumber, y::GaussNumber)
    while(y.a != 0 || y.b != 0)
        x, y = y, divWithRest(x, y)[2]
    end
    return x
end

function nww(x::GaussNumber, y::GaussNumber)
    if(y.a == 0 && y.b == 0)
        return y
    end
    return x / nwd(x, y) * y
end

function findSpecificIdeal()
    a = GaussNumber(3, 4)
    b = GaussNumber(1, 3)
    c = nwd(a, b)
    d = nww(a, b)
    return c, d
end

b = GaussNumber(2, 2)
c = GaussNumber(2, 1)
println(findSpecificIdeal())