# author: Jakub Drzewiecki 268418

# Find value of macheps for given type
# t - type of values, accepted values are Float16, Float32 and Float64
function macheps(t)
    return t(3) * (t(4)/t(3) - t(1)) - t(1)
end

# Main function, show result of my functions
function main()
    println("Macheps")
    println("Float16: ", macheps(Float16))
    println("Float32: ", macheps(Float32))
    println("Float64: ", macheps(Float64))
    println("Funkcja eps")
    println("Float16: ", eps(Float16))
    println("Float32: ", eps(Float32))
    println("Float64: ", eps(Float64))
end

main()