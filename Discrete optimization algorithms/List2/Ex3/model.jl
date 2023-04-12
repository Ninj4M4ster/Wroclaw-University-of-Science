import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")
import Pkg

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

G_min = [
    2 4 3
    3 6 5
    5 7 6
]

G_max = [
    3 7 5
    5 7 10
    8 12 10
]

shift_min = [10, 20, 18]

district_min = [10, 14, 13]

n = size(G_min)[1]

# Zmienna decyzyjna
@variable(model, result_graph[1:n, 1:n] >= 0)

@constraint(model, [i = 1:n, j = 1:n], G_min[i, j] <= result_graph[i, j] <= G_max[i, j])

@constraint(model, [i = 1:n], sum(result_graph[i, :]) >= district_min[i])

@constraint(model, [i = 1:n], sum(result_graph[:, i]) >= shift_min[i])

@objective(model, Min, sum(result_graph[:, :]))