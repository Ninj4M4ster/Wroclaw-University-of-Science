# Jakub Drzewiecki

include("model.jl")

optimize!(model)

value.(result_graph)