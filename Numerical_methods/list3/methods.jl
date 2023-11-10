# author: Jakub Drzewiecki 268418

function mbisekcji(f, a::Float64, b::Float64, delta::Float64, epsilon::Float64)
    iteration_counter = 0
    u = f(a)
    v = f(b)
    e = b - a
    if(sign(u) == sign(v))
        return 0, 0, 0, 1
    end
    while true
        iteration_counter += 1
        e = e / 2.0
        r = a + e
        w = f(r)
        if(abs(w) < epsilon || abs(e) < delta)
            return r, w, iteration_counter, 0
        end
        if(sign(w) != sign(u))
            b = r
        else
            a = r
            u = w
        end
    end
end

function mstycznych(f, pf, x0::Float64, delta::Float64, epsilon::Float64, maxit::Int)
    iteration_counter = 0
    v = f(x0)
    if(abs(v) < epsilon)
        return x0, v, iteration_counter, 0
    end
    while true
        if(abs(pf(x0)) < 0.000000001)  # find better way to check if pf is close to 0 
            return x0, v, iteration_counter, 2
        end
        iteration_counter += 1
        x1 = x0 - v/pf(x0)
        v = f(x1)
        if(abs(x1 - x0) < delta || abs(v) < epsilon)  # accuracy achieved
            return x1, v, iteration_counter, 0
        end
        if(iteration_counter == maxit)  # not enough iterations
            return x1, v, iteration_counter, 1
        end
        x0 = x1
    end
end

function msiecznych(f, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64, maxit::Int)
    iteration_counter = 0
    fx0 = f(x0)
    fx1 = f(x1)
    while(true)
        if(iteration_counter == maxit)
            return x0, fx0, iteration_counter, 1
        end
        iteration_counter += 1
        if abs(fx0) > abs(fx1)
            x0, x1 = x1, x0
            fx0, fx1 = fx1, fx0
        end
        s = (x1 - x0) / (fx1 - fx0)
        x1 = x0
        fx1 = fx0
        x0 = x0 - fx0 * s
        fx0 = f(x0)
        if(abs(x1 - x0) < delta || abs(fx0) < epsilon)
            return x0, fx0, iteration_counter, 0
        end
    end
end

function main()
    a = -0.5
    b = 1.0
    f = x -> sin(x)
    fp = x -> cos(x)
    mbisekcji(f, -0.5, 0.25, 0.01, 0.01)
end

main()
