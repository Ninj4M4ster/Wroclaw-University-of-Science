# Jakub Drzewiecki

import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")
import Pkg

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

# Koszta przejść między wierzchołkami
G_cost = [
    0 6.2 0 0 0 2.1 0 0 3.4 0 0 0 0 0 0
    0 0 0 0 1.1 0 0 0 0 0 0 0 0 0 0
    1.15 0 0 1.67 0 0 0 0 0 0 0 0 0 0 0
    15.23 0 0 0 0 0 0 0 0 1.2 0 0 0 0 0
    0 0 0 1.8 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 3.9 0 0 0 0 0 0 0 0 0 0
    0 0 0 3.12 0 0 0 0 0 5.45 1.7 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 3.1 0
    0 0 6.76 0 0 0 2.165 0 0 0 0 0 0 0 0
    0 0 0 0 2.89 0 2.56 4.765 0 0 0 2.23 0 0 0
    0 0 0 0 0 0 0 0 0 12.76 0 0 0 0 5.12
    0 0 0 0 0 0 0 0 0 0 0 0 0 1.56 1.76
    0 0 0 0 1.11 0 0 1.94 0 0 0 0 0 10.76 0
    0 0 0 0 0 0 0 0 0 3.83 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 7.87 0 0 0 0 0
]

# Czasy przejść między wierzchołkami
G_time = [
    0 1.9 0 0 0 5.3 0 0 3.7 0 0 0 0 0 0
    0 0 0 0 7.11 0 0 0 0 0 0 0 0 0 0
    10.53 0 0 6 0 0 0 0 0 0 0 0 0 0 0
    1.16 0 0 0 0 0 0 0 0 10.67 0 0 0 0 0
    0 0 0 7.865 0 0 0 0 0 0 0 0 0 0 0
    0 0 0 0 3.75 0 0 0 0 0 0 0 0 0 0
    0 0 0 3.73 0 0 0 0 0 5.72 18.86 0 0 0 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 6.82 0
    0 0 2.16 0 0 0 5.67 0 0 0 0 0 0 0 0
    0 0 0 0 4.1632 0 6.346 3.7 0 0 0 6.61 0 0 0
    0 0 0 0 0 0 0 0 0 1.97 0 0 0 0 2.74
    0 0 0 0 0 0 0 0 0 0 0 0 0 5.37 4.18
    0 0 0 0 8.37 0 0 12.7234 0 0 0 0 0 2.61 0
    0 0 0 0 0 0 0 0 0 3.73 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 2.17 0 0 0 0 0
]
n = size(G_cost)[1]
b = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1]
T = 30

# Zmienna przechowujaca graf wynikowy
@variable(model, result_graph[1:n, 1:n] >= 0)
# Ograniczenie na przeplyw miedzy miastami ktore nie posiadaja polaczen
@constraint(model, [i = 1:n, j = 1:n; G_cost[i, j] == 0], result_graph[i, j] == 0)
# Ograniczenie na czas przeplywu
@constraint(model, sum(result_graph .* G_time) <= T)
# Ograniczenie na startowe i końcowe miasto
@constraint(model, [i = 1:n], sum(result_graph[i, :]) - sum(result_graph[:, i]) == b[i])

@objective(model, Min, sum(result_graph .* G_cost))