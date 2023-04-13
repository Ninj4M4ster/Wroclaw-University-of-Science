include("model.jl")

print(model)

optimize!(model)

println("P1 = ", value(p1))
println("P2 = ", value(p2))
println("P3 = ", value(p3))
println("P4 = ", value(p4))
println("M1 = ", value(m1))
println("M2 = ", value(m2))
println("M3 = ", value(m3))

println("\nFinalny zysk tygodniowy = ", objective_value(model))
