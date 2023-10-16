# author: Jakub Drzewiecki 268418

function find_macheps_float16() 
    one = Float16(1)
    added_number = Float16(1)
    while(one + added_number / Float16(2) > one) 
        added_number /= Float16(2)
    end
    return added_number
end

function find_macheps_float32() 
    one = Float32(1)
    added_number = Float32(1)
    while(one + added_number / Float32(2) > one) 
        added_number /= Float32(2)
    end
    return added_number
end

function find_macheps_float64() 
    one = Float64(1)
    added_number = Float64(1)
    while(one + added_number / Float64(2) > one) 
        added_number /= Float64(2)
    end
    return added_number
end

function find_eta_float16()
    one = Float16(1)
    while(one / Float16(2) > Float16(0))
        one /= Float16(2)
    end
    return one
end

function find_eta_float32()
    one = Float32(1)
    while(one / Float32(2) > Float32(0))
        one /= Float32(2)
    end
    return one
end

function find_eta_float64()
    one = Float64(1)
    while(one / Float64(2) > Float64(0))
        one /= Float64(2)
    end
    return one
end

function find_max_float16()
    one = Float16(1)
    while(!isinf(one * Float16(2)))
        one *= Float16(2)
    end
    half = one / Float16(2)
    while(half > Float16(1) && !isinf(one + half))
        one += half
        half /= Float16(2)
    end
    return one
end

println(find_max_float16())
floatmax(Float16)
# find_macheps_float64()
# eps(Float64)
# find_eta_float64()
# nextfloat(Float64(0.0))