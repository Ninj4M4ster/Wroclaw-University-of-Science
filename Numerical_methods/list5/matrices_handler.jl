# author: Jakub Drzewiecki 268418

struct SMatrix 
    matrix::Dict{Int64, Dict{Int64, Float64}}
    max_rows_indexes::Vector{Int64}
    matrix_dim::Int64
    submatrix_dim::Int64
end

function readMatrixFromFile(file_name::String)
    f = open(file_name, "r")
    first_line = split(readline(f))
    matrix_dim = parse(Int64, first_line[1])
    submatrix_dim = parse(Int64, first_line[2])

    matrix = Dict{Int64, Dict{Int64, Float64}}()
    max_rows_indexes = zeros(Int64, matrix_dim)
    for i = 1:matrix_dim
        matrix[i] = Dict{Int64, Float64}()
    end

    for line in readlines(f)
        vals = split(line)
        i_index = parse(Int64, vals[1])
        j_index = parse(Int64, vals[2])
        value = parse(Float64, vals[3])
        matrix[i_index][j_index] = value
        if(max_rows_indexes[j_index] < i_index)
            max_rows_indexes[j_index] = i_index
        end
    end
    close(f)
    return SMatrix(matrix, max_rows_indexes, matrix_dim, submatrix_dim)
end

function readRightSideVectorFromFile(file_name::String)
    f = open(file_name, "r")
    b = Vector{Float64}()
    size = readline(f)
    for i = 1:size
        line = readline(f)
        append!(b, parse(Float64, line))
    end
    close(f)
    return b
end

export SMatrix