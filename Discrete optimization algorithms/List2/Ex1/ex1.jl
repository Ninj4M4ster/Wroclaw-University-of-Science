include("model.jl")

print(model)

optimize!(model)

println("X1 = ", value(x1))
println("X2 = ", value(x2))
println("X3 = ", value(x3))
