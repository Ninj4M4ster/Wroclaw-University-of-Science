# Jakub Drzewiecki

include("new_model.jl")

print(model)

optimize!(model)

value.(X)