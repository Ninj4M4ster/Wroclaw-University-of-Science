# author: Jakub Drzewiecki 268418

"""
Struktura reprezentująca rzadką macierz.
"""
struct SMatrix 
    matrix::Dict{Int64, Dict{Int64, Float64}}
    max_rows_indexes::Vector{Int64}
    matrix_dim::Int64
end

"""
Funkcja wczytująca macierz z podanego pliku do jej rzadkiej reprezentacji.

@param file_name - nazwa pliku, w którym zapisana jest macierz do wczytania.

@return rzadka reprezentacja wczytanej macierzy.
"""
function readMatrixFromFile(file_name::String)
    f = open(file_name, "r")
    first_line = split(readline(f))
    matrix_dim = parse(Int64, first_line[1])

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
    return SMatrix(matrix, max_rows_indexes, matrix_dim)
end

"""
Funkcja wczytująca wektor prawych stron z podanego pliku.

@param file_name - nazwa pliku, w którym zapisany jest wektor prawych stron do wczytania.

@return wektor prawych stron.
"""
function readRightSideVectorFromFile(file_name::String)
    f = open(file_name, "r")
    b = Vector{Float64}()
    size = parse(Int64, readline(f))
    for i = 1:size
        line = readline(f)
        append!(b, parse(Float64, line))
    end
    close(f)
    return b
end

"""
Funkcja generująca wektor prawych stron na podstawie zadanej macierzy współczynników A rozmiarów n x n
z założeniem, że rozwiązaniem równania Ax = b jest wektor jedynek.

@param A - macierz współczynników w rzadkiej reprezentacji.

@return wektor prawych stron.
"""
function generateRightSideVector(A::Main.SMatrix)
    b = zeros(A.matrix_dim)
    for i = 1:A.matrix_dim
        sum = 0.0
        for val in values(A.matrix[i])
            sum += val
        end
        b[i] = sum
    end
    return b
end

"""
Funkcja wypisująca do podanego pliku rozwiązanie równania Ax = b.

@param x - rozwiązanie równania Ax = b.
@param file_name - nazwa pliku, w którym zapisane zostaną dane.
"""
function outputX(x::Vector{Float64}, file_name::String)
    f = open(file_name, "w")
    for i = eachindex(x)
        str = string(x[i])
        write(f, str)
        write(f, "\n")
    end
    close(f)
end

"""
Funkcja wypisująca do podanego pliku rozwiązanie równania Ax = b, gdy wektor prawych stron został wygenerowany wektorem jedynek.
W pierwszym wierszu znajduje się również błąd względny rozwiązania.

@param x - rozwiązanie równania Ax = b.
@param file_name - nazwa pliku, w którym zapisane zostaną dane.
"""
function outputGeneratedX(x::Vector{Float64}, file_name::String)
    x_original = ones(length(x))
    error = sum(abs.(abs.(x) - abs.(x_original))) / length(x)

    f = open(file_name, "w")
    str = string(error)
    write(f, str)
    write(f, "\n")
    for i = eachindex(x)
        str = string(x[i])
        write(f, str)
        write(f, "\n")
    end
    close(f)
end