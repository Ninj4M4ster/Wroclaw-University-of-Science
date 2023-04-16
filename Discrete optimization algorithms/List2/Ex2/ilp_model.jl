# Jakub Drzewiecki

import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")
import Pkg

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

G_cost = [
    0 6 0 0 0 2 0 0 3 0 0 0 0 0 0
    0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
    1 0 0 1 0 0 0 0 0 0 0 0 0 0 0
    15 0 0 0 0 0 0 0 0 1 0 0 0 0 0
    0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 3 0 0 0 0 0 0 0 0 0 0
    0 0 0 3 0 0 0 0 0 5 1 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 3 0
    0 0 6 0 0 0 2 0 0 0 0 0 0 0 0
    0 0 0 0 2 0 2 4 0 0 0 2 0 0 0
    0 0 0 0 0 0 0 0 0 12 0 0 0 0 5
    0 0 0 0 0 0 0 0 0 0 0 0 0 1 1
    0 0 0 0 1 0 0 1 0 0 0 0 0 10 0
    0 0 0 0 0 0 0 0 0 3 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 7 0 0 0 0 0
]

G_time = [
    0 1 0 0 0 5 0 0 3 0 0 0 0 0 0
    0 0 0 0 7 0 0 0 0 0 0 0 0 0 0
    10 0 0 6 0 0 0 0 0 0 0 0 0 0 0
    1 0 0 0 0 0 0 0 0 10 0 0 0 0 0
    0 0 0 7 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 3 0 0 0 0 0 0 0 0 0 0
    0 0 0 3 0 0 0 0 0 5 18 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 6 0
    0 0 2 0 0 0 5 0 0 0 0 0 0 0 0
    0 0 0 0 4 0 6 3 0 0 0 6 0 0 0
    0 0 0 0 0 0 0 0 0 1 0 0 0 0 2
    0 0 0 0 0 0 0 0 0 0 0 0 0 5 4
    0 0 0 0 8 0 0 12 0 0 0 0 0 2 0
    0 0 0 0 0 0 0 0 0 3 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 2 0 0 0 0 0
]
n = size(G_cost)[1]
b = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1]
T = 25

# Zmienna przechowujaca graf wynikowy
@variable(model, result_graph[1:n, 1:n], Bin)
# Ograniczenie na przeplyw miedzy miastami ktore nie posiadaja polaczen
@constraint(model, [i = 1:n, j = 1:n; G_cost[i, j] == 0], result_graph[i, j] == 0)
# Ograniczenie na czas przeplywu
@constraint(model, sum(result_graph .* G_time) <= T)
# Ograniczenie na startowe i końcowe miasto
@constraint(model, [i = 1:n], sum(result_graph[i, :]) - sum(result_graph[:, i]) == b[i])

@objective(model, Min, sum(result_graph .* G_cost))