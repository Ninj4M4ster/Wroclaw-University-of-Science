# author: Jakub Drzewiecki 268418

include("blocksys.jl")
using Main.blocksys

function main()
    A_matrix_file_name = "G:/Programowanie/Wroclaw-University-of-Science/Numerical_methods/list5/dane/Dane500000_1_1/A.txt"
    b_right_side_vector_file_name = "G:/Programowanie/Wroclaw-University-of-Science/Numerical_methods/list5/dane/Dane500000_1_1/b.txt"
    A = readMatrixFromFile(A_matrix_file_name)
    b = readRightSideVectorFromFile(b_right_side_vector_file_name)
    gaussElimination(A, b)
end

main()