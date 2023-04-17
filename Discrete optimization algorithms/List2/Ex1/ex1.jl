# Jakub Drzewiecki

include("model.jl")

print(model)

optimize!(model)

println("\nIlosc paliw dostarczone na lotniska")
println("l1 = ", value(X[1, 1]) + value(X[1, 2]) + value(X[1, 3]))
println("l2 = ", value(X[2, 1]) + value(X[2, 2]) + value(X[2, 3]))
println("l3 = ", value(X[3, 1]) + value(X[3, 2]) + value(X[3, 3]))
println("l4 = ", value(X[4, 1]) + value(X[4, 2]) + value(X[4, 3]))
println("\nIlosc paliw dostarczane przez poszczegolne firmy")
println("f1 = ", value(sum(X[:, 1])))
println("f2 = ", value(sum(X[:, 2])))
println("f3 = ", value(sum(X[:, 3])))
println("\nSumaryczny koszt = ", objective_value(model))
println("\nPaliwa dostarczone na poszczegolne lotniska")
value.(X)