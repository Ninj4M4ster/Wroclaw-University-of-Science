# author: Jakub Drzewiecki 268418

# Find value of macheps for Float16 type
function find_macheps_float16() 
    one = Float16(1)
    added_number = Float16(1)
    while(one + added_number / Float16(2) > one) 
        added_number /= Float16(2)
    end
    return added_number
end

# Find value of macheps for Float32 type
function find_macheps_float32() 
    one = Float32(1)
    added_number = Float32(1)
    while(one + added_number / Float32(2) > one) 
        added_number /= Float32(2)
    end
    return added_number
end

# Find value of macheps for Float64 type
function find_macheps_float64() 
    one = Float64(1)
    added_number = Float64(1)
    while(one + added_number / Float64(2) > one) 
        added_number /= Float64(2)
    end
    return added_number
end

# Find value of eta for Float16 type
function find_eta_float16()
    one = Float16(1)
    while(one / Float16(2) > Float16(0))
        one /= Float16(2)
    end
    return one
end

# Find value of eta for Float32 type
function find_eta_float32()
    one = Float32(1)
    while(one / Float32(2) > Float32(0))
        one /= Float32(2)
    end
    return one
end

# Find value of eta for Float64 type
function find_eta_float64()
    one = Float64(1)
    while(one / Float64(2) > Float64(0))
        one /= Float64(2)
    end
    return one
end

# Find value of MAX for Float16 type
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

# Find value of MAX for Float32 type
function find_max_float32()
    one = Float32(1)
    while(!isinf(one * Float32(2)))
        one *= Float32(2)
    end
    half = one / Float32(2)
    while(half > Float32(1) && !isinf(one + half))
        one += half
        half /= Float32(2)
    end
    return one
end

# Find value of MAX for Float64 type
function find_max_float64()
    one = Float64(1)
    while(!isinf(one * Float64(2)))
        one *= Float64(2)
    end
    half = one / Float64(2)
    while(half > Float64(1) && !isinf(one + half))
        one += half
        half /= Float64(2)
    end
    return one
end

# Main function, show result of my functions
function main()
    println("Macheps")
    println("Float16: ", find_macheps_float16())
    println("Float32: ", find_macheps_float32())
    println("Float64: ", find_macheps_float64())
    println("Funkcje eps")
    println("Float16: ", eps(Float16))
    println("Float32: ", eps(Float32))
    println("Float64: ", eps(Float64))
    println("Eta")
    println("Float16: ", find_eta_float16())
    println("Float32: ", find_eta_float32())
    println("Float64: ", find_eta_float64())
    println("Funkcje nextfloat")
    println("Float16: ", nextfloat(Float16(0.0)))
    println("Float32: ", nextfloat(Float32(0.0)))
    println("Float64: ", nextfloat(Float64(0.0)))
    println("Funkcja floatmin")
    println("Float32: ", floatmin(Float32))
    println("Float64: ", floatmin(Float64))
    println("MAX")
    println("Float16: ", find_max_float16())
    println("Float32: ", find_max_float32())
    println("Float64: ", find_max_float64())
    println("Funkcja floatmax")
    println("Float16: ", floatmax(Float16))
    println("Float32: ", floatmax(Float32))
    println("Float64: ", floatmax(Float64))
end

main()