include("model.jl")

print(model)

optimize!(model)

println("\nIlosc paliw dostarczone na lotniska")
println("l1 = ", value(x11) + value(x12) + value(x13))
println("l2 = ", value(x21) + value(x22) + value(x23))
println("l3 = ", value(x31) + value(x32) + value(x33))
println("l4 = ", value(x41) + value(x42) + value(x43))
println("\nSumaryczny koszt = ", objective_value(model))
println("\nPaliwa dostarczone na poszczegolne lotniska")
value.(X)