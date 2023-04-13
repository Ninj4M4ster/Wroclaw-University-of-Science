import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")
import Pkg

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

# Minimalna ilosc dostepnych radiowozow w dzielnicach podczas poszczegolnych zmiana
G_min = [
    2 4 3
    3 6 5
    5 7 6
]

# Maksymalna ilosc dostepnych radiowozow w dzielnicach podczas poszczegolnych zmian
G_max = [
    3 7 5
    5 7 10
    8 12 10
]

# Minimalna sumaryczna ilosc radiowozow dla poszczegolnych zmian
shift_min = [10, 20, 18]

# Minimalna sumaryczna ilosc radiowozow dla poszczegolnych dzielnic
district_min = [10, 14, 13]

n = size(G_min)[1]

# Zmienna decyzyjna
@variable(model, result_graph[1:n, 1:n] >= 0)

# Zmienna decyzyjna musi sie zawierac w przedziale wyznaczonym przez minimalne i maksymalne ilosci dostepnych radiowozow
@constraint(model, [i = 1:n, j = 1:n], G_min[i, j] <= result_graph[i, j] <= G_max[i, j])

# Ograniczenie na minimalna sumaryczna ilosc radiowozow w poszczegolnych dzielnicach
@constraint(model, [i = 1:n], sum(result_graph[i, :]) >= district_min[i])

# Ograniczenie na minimalna sumaryczna ilosc radiowozow podczas poszczegolnych zmian
@constraint(model, [i = 1:n], sum(result_graph[:, i]) >= shift_min[i])

# Funkcja celu
@objective(model, Min, sum(result_graph[:, :]))