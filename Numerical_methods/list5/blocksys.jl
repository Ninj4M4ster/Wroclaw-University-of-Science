# author: Jakub Drzewiecki 268418

include("matrices_handler.jl")

module blocksys

export gaussElimination, gaussEliminationPartialChoice, luDistribution, luDistributionPartialChoice, solveWithLU, solveWithPivotedLU

"""
Funkcja obliczająca rozwiązanie x układu równań Ax=b za pomocą metody eliminacji gaussa bez wyboru elementu głównego.

@param A - macierz współczynników rozmiarów n x n w reprezentacji macierzy rzadkiej.
@param b - wektor prawych stron.

@result rozwiązanie x układu równań Ax = b.
"""
function gaussElimination(A::Main.SMatrix, b::Vector{Float64})
    # Sprowadzenie do macierzy trójkątnej z uwzględnieniem granicznych wartości niezerowych w danej kolumnie/rzędzie
    for k = 1:A.matrix_dim - 1
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            I = A.matrix[row][k] / A.matrix[k][k]
            A.matrix[row][k] = 0.0

            for column = k+1:maximum(collect(keys(A.matrix[k])))
                if(!haskey(A.matrix[k], column))
                    continue
                end
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
            b[row] -= I * b[k]
        end
    end

    # Znalezienie rozwiązania
    x = zeros(A.matrix_dim)
    x[A.matrix_dim] = b[A.matrix_dim] / A.matrix[A.matrix_dim][A.matrix_dim]
    for k = A.matrix_dim - 1:-1:1
        sum = 0.0
        for j = k+1:maximum(collect(keys(A.matrix[k])))
            if(!haskey(A.matrix[k], j))
                continue
            end
            sum += A.matrix[k][j] * x[j]
        end
        x[k] = (b[k] - sum) / A.matrix[k][k]
    end
    return x
end

"""
Funkcja obliczająca rozwiązanie x układu równań Ax=b za pomocą metody eliminacji gaussa z częściowym wyborem elementu głównego.

@param A - macierz współczynników rozmiarów n x n w reprezentacji macierzy rzadkiej.
@param b - wektor prawych stron.

@result rozwiązanie x układu równań Ax = b.
"""
function gaussEliminationPartialChoice(A::Main.SMatrix, b::Vector{Float64})
    # Sprowadzenie do macierzy trójkątnej z uwzględnieniem granicznych wartości niezerowych w danej kolumnie/rzędzie
    for k = 1:A.matrix_dim - 1
        # Częściowy wybór elementu głównego
        max_a = 0.0
        max_ind = k
        zero_val_row = true
        if(haskey(A.matrix[k], k))
            max_a = abs(A.matrix[k][k])
            zero_val_row = false
        end
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            if(abs(A.matrix[row][k]) > max_a)
                max_a = abs(A.matrix[row][k])
                max_ind = row
                zero_val_row = false
            end
        end
        if(max_ind != k)
            A.matrix[max_ind], A.matrix[k] = A.matrix[k], A.matrix[max_ind]
            b[max_ind], b[k] = b[k], b[max_ind]
            # Aktualizacja indeksu ostatniego rzędu w danej kolumnie z niezerową wartością
            if(zero_val_row)
                ind = A.max_rows_indexes[k]
                while(!haskey(A.matrix[ind], k))
                    ind -= 1
                end
                A.max_rows_indexes[k] = ind
            end
        end
        # Eliminacja
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            I = A.matrix[row][k] / A.matrix[k][k]
            A.matrix[row][k] = 0.0

            for column = k+1:maximum(collect(keys(A.matrix[k])))
                if(!haskey(A.matrix[k], column))
                    continue
                end
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
            b[row] -= I * b[k]
        end
    end

    # Znalezienie rozwiązania
    x = zeros(A.matrix_dim)
    x[A.matrix_dim] = b[A.matrix_dim] / A.matrix[A.matrix_dim][A.matrix_dim]
    for k = A.matrix_dim - 1:-1:1
        sum = 0.0
        for j = k+1:maximum(collect(keys(A.matrix[k])))
            if(!haskey(A.matrix[k], j))
                continue
            end
            sum += A.matrix[k][j] * x[j]
        end
        x[k] = (b[k] - sum) / A.matrix[k][k]
    end
    return x
end

"""
Funkcja wyznaczająca rozkład LU macierzy A za pomocą eliminacji gaussa bez wyboru elementu głównego.

@param A - macierz współczynników rozmiarów n x n w reprezentacji macierzy rzadkiej.

@result rozkład LU macierzy A w reprezentacji macierzy rzadkiej.
"""
function luDistribution(A::Main.SMatrix)
    # Kopia macierzy A zostanie wynikową macierzą LU
    # Sprowadzenie do macierzy trójkątnej z uwzględnieniem granicznych wartości niezerowych w danej kolumnie/rzędzie
    for k = 1:A.matrix_dim - 1
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            I = A.matrix[row][k] / A.matrix[k][k]
            # Uzupełnienie zerowanej wartości w macierzy LU
            A.matrix[row][k] = I

            for column = k+1:maximum(collect(keys(A.matrix[k])))
                if(!haskey(A.matrix[k], column))
                    continue
                end
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
        end
    end

    return A
end

"""
Funkcja wyznaczająca rozkład LU macierzy A za pomocą eliminacji gaussa z częściowym wyborem elementu głównego.

@param A - macierz współczynników rozmiarów n x n w reprezentacji macierzy rzadkiej.

@result para zmiennych - rozkład LU macierzy A w reprezentacji macierzy rzadkiej; wektor par indeksów wierszy, które zostały zamienione miejscami.
"""
function luDistributionPartialChoice(A::Main.SMatrix)
    # Kopia macierzy A zostanie wynikową macierzą LU
    pivots = Vector{Int64}[]
    # Sprowadzenie do macierzy trójkątnej z uwzględnieniem granicznych wartości niezerowych w danej kolumnie/rzędzie
    for k = 1:A.matrix_dim - 1
        # Częściowy wybór elementu głównego
        max_a = 0.0
        max_ind = k
        zero_val_row = true
        if(haskey(A.matrix[k], k))
            max_a = abs(A.matrix[k][k])
            zero_val_row = false
        end
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            if(abs(A.matrix[row][k]) > max_a)
                max_a = abs(A.matrix[row][k])
                max_ind = row
                zero_val_row = false
            end
        end
        if(max_ind != k)
            A.matrix[max_ind], A.matrix[k] = A.matrix[k], A.matrix[max_ind]
            push!(pivots, [max_ind, k])
            # Aktualizacja indeksu ostatniego rzędu w danej kolumnie z niezerową wartością
            if(zero_val_row)
                ind = A.max_rows_indexes[k]
                while(!haskey(A.matrix[ind], k))
                    ind -= 1
                end
                A.max_rows_indexes[k] = ind
            end
        end
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            I = A.matrix[row][k] / A.matrix[k][k]
            # Uzupełnienie zerowanej wartości w macierzy LU
            A.matrix[row][k] = I

            for column = k+1:maximum(collect(keys(A.matrix[k])))
                if(!haskey(A.matrix[k], column))
                    continue
                end
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
        end
    end

    return A, pivots
end

"""
Funkcja rozwiązująca układ równań Ax = b za pomocą wyznaczonego wcześniej 
metodą eliminacji gaussa bez wyboru elementu głównego rozkładu LU.

@param LU - rozkład LU macierzy A.
@param b - wektor prawych stron.

@result rozwiązanie x układu równań Ax = b.
"""
function solveWithLU(LU::Main.SMatrix, b::Vector{Float64})
    for k = 1:LU.matrix_dim - 1
        for row = k+1:LU.max_rows_indexes[k]
            if(haskey(LU.matrix[k], row))
                b[row] -= LU.matrix[row][k] * b[k]
            end
        end
    end

    x = zeros(LU.matrix_dim)
    x[LU.matrix_dim] = b[LU.matrix_dim] / LU.matrix[LU.matrix_dim][LU.matrix_dim]
    for k = LU.matrix_dim:-1:1
        sum = 0.0
        for j = k+1:maximum(collect(keys(LU.matrix[k])))
            if(!haskey(LU.matrix[k], j))
                continue
            end
            sum += LU.matrix[k][j] * x[j]
        end
        x[k] = (b[k] - sum) / LU.matrix[k][k]
    end
    return x
end

"""
Funkcja rozwiązująca układ równań Ax = b za pomocą wyznaczonego wcześniej 
metodą eliminacji gaussa z częściowym wyborem elementu głównego rozkładu LU.

@param LU - rozkład LU macierzy A.
@param b - wektor prawych stron.
@param pivots - wektor par indeksów wierszy, które zostały zamienione miejscami.

@result rozwiązanie x układu równań Ax = b.
"""
function solveWithPivotedLU(LU::Main.SMatrix, b::Vector{Float64}, pivots::Vector{Vector{Int64}})
    for i = eachindex(pivots)
        b[pivots[i][1]], b[pivots[i][2]] = b[pivots[i][2]], b[pivots[i][1]]
    end
    return solveWithLU(LU, b)
end

end