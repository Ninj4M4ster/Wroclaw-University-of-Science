# author: Jakub Drzewiecki 268418

include("blocksys.jl")
using Main.blocksys

"""
Funkcja testująca zaimplementowane algorytmy na podstawie podanych parametrów.

@param A_matrix_file_name - nazwa pliku, w którym znajduje się macierz współczynników A.
@param b_right_side_vector_file_name - nazwa pliku, w którym znajduje się wektor prawych stron.
@param generate_b - czy wektor prawych stron powinien zostać wygenerowany?
@param pivoting - czy powinny zostać użyte warianty algorytmów z częściowym wyborem elementu głównego?
@param LU_usage - czy równanie powinno zostać rozwiązane za pomocą rozkładu LU?
@param output_file_name - nazwa pliku, w którym zapisane zostanie rozwiązanie.
"""
function test(A_matrix_file_name::String, b_right_side_vector_file_name::String, generate_b::Bool, pivoting::Bool, LU_usage::Bool, output_file_name::String)
    A = readMatrixFromFile(A_matrix_file_name)
    b = ones(A.matrix_dim)
    if(!generate_b)
        b = readRightSideVectorFromFile(b_right_side_vector_file_name)
    else
        b = generateRightSideVector(A)
    end

    result = 0.0

    if(!LU_usage)
        if(!pivoting)
            result = gaussElimination(A, b)
        else
            result = gaussEliminationPartialChoice(A, b)
        end
        if(generate_b)
            outputGeneratedX(result, output_file_name)
        else
            outputX(result, output_file_name)
        end
    else
        if(!pivoting)
            LU = luDistribution(A)
            result = solveWithLU(LU, b)
        else
            LU, p = luDistributionPartialChoice(A)
            result = solveWithPivotedLU(LU, b, p)
        end
        if(generate_b)
            outputGeneratedX(result, output_file_name)
        else
            outputX(result, output_file_name)
        end
    end
end

function main()
    A_matrix_file_name = "dane/Dane500000_1_1/A.txt"
    b_right_side_vector_file_name = "dane/Dane500000_1_1/b.txt"
    output_file_name = "result.txt"
    generate_b = false
    pivoting = false
    LU_usage = false

    test(A_matrix_file_name, b_right_side_vector_file_name, generate_b, pivoting, LU_usage, output_file_name)
end

main()
