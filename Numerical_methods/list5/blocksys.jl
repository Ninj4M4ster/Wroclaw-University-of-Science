# author: Jakub Drzewiecki

module blocksys

include("matrices_handler.jl")

function gaussElimination(A::SMatrix, b::Vector{Float64})
    # Sprowadzenie do macierzy trójkątnej z uwzględnieniem granicznych wartości niezerowych w danej kolumnie/rzędzie
    for k = 1:A.matrix_dim - 1
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            I = A.matrix[row][k] / A.matrix[k][k]
            A.matrix[row][k] = 0.0

            for column = 1:max(keys(A.matrix[row]))
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
            b[row] -= I * b[k]
        end
    end

    # Znalezienie rozwiązań
    x = zeros(A.matrix_dim)
    x[A.matrix_dim] = b[A.matrix_dim] / A.matrix[A.matrix_dim][A.matrix_dim]
    for k = A.matrix_dim - 1:-1:1
        sum = 0.0
        for j = k+1:max(keys(A.matrix[k]))
            sum += A.matrix[k][j] * x[j]
        end
        x[k] = (b[k] - sum) / A.matrix[k][k]
    end
    return x
end

function gaussEliminationPartialChoice(A::SMatrix, b::Vector{Float64})
    # Sprowadzenie do macierzy trójkątnej z uwzględnieniem granicznych wartości niezerowych w danej kolumnie/rzędzie
    for k = 1:A.matrix_dim - 1
        # Częściowy wybór elementu głównego
        max_a = 0.0
        max_ind = k
        zero_val_row = true
        if(haskey(A.matrix[row], k))
            max_a = abs(A.matrix[k][k])
        end
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            if(abs(A.matrix[row][k]) > max_a)
                max_a = abs(A.matrix[row][k])
                max_ind = row
            end
        end
        if(max_ind != k)
            A.matrix[max_ind], A.matrix[k] = A.matrix[k], A.matrix[max_ind]
            b[max_ind], b[k] = b[k], b[max_ind]
            # Aktualizacja indeksu ostatniego rzędu w danej kolumnie z niezerową wartością
            if(zero_val_row)

            end
        end
        # Eliminacja
        for row = k+1:A.max_rows_indexes[k]
            if(!haskey(A.matrix[row], k))
                continue
            end
            I = A.matrix[row][k] / A.matrix[k][k]
            A.matrix[row][k] = 0.0

            for column = 1:max(keys(A.matrix[row]))
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
            b[row] -= I * b[k]
        end
    end

    # Znalezienie rozwiązań
    x = zeros(A.matrix_dim)
    x[A.matrix_dim] = b[A.matrix_dim] / A.matrix[A.matrix_dim][A.matrix_dim]
    for k = A.matrix_dim - 1:-1:1
        sum = 0.0
        for j = k+1:max(keys(A.matrix[k]))
            sum += A.matrix[k][j] * x[j]
        end
        x[k] = (b[k] - sum) / A.matrix[k][k]
    end
    return x
end

function luDistribution(A::SMatrix)
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

            for column = 1:max(keys(A.matrix[row]))
                if(!haskey(A.matrix[row], column))
                    A.matrix[row][column] = 0.0
                end
                A.matrix[row][column] -= I * A.matrix[k][column]
            end
        end
    end

    return A
end

end