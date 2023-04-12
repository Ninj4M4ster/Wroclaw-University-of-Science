include("model.jl")

print(model)

optimize!(model)

solution_summary(model; verbose=true)
