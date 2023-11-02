# author: Jakub Drzewiecki 268418

include("extras.jl")

# Generate Hilbert matrix.
# n - dimension of matrix
function generate_A(n::Int)
    return hilb(n)
end

# Generate random matrix.
# n - dimension of matrix
# c - conditioning of matrix
function generate_A(n::Int, c::Float64)
    return matcond(n, c)
end

# Main function, it generate results of the experiments.
function main()
    println("Hilbert")
    for i = 1:60
        A = generate_A(i)
        X = ones(Float64, (i,1))
        b = A * X
        x_r = A \ b
        x_r_err = sum(abs.(X-x_r))
        x_r_2 = inv(A) * b
        x_r_2_err = sum(abs.(X - x_r_2))
        println("N: ", i, ", gauss_err: ", x_r_err, ", inv error: ", x_r_2_err, ", cond: ", cond(A), ", rank: ", rank(A))
    end

    println("\nRandom matrix")
    for i in [5,10,20]
        for c in [1.0, 10.0, 10.0^3, 10.0^7, 10.0^12, 10.0^16]
            A = generate_A(i, c)
            X = ones(Float64, (i,1))
            b = A * X
            x_r = A \ b
            x_r_err = sum(abs.(X-x_r))
            x_r_2 = inv(A) * b
            x_r_2_err = sum(abs.(X - x_r_2))
            println("N: ", i, ", c: ", c ,", gauss_err: ", x_r_err, ", inv error: ", x_r_2_err, ", rank: ", rank(A))
        end
    end
end

main()