# author: Jakub Drzewiecki 268418

include("blocksys.jl")
using Main.blocksys

function main()
    A_matrix_file_name = "G:/Programowanie/Wroclaw-University-of-Science/Numerical_methods/list5/dane/Dane16_1_1/A.txt"
    readMatrixFromFile(A_matrix_file_name)
end

main()