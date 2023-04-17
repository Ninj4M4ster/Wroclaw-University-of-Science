# Jakub Drzewiecki

import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")
import Pkg

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

# Minimalna ilosc dostepnych radiowozow w dzielnicach podczas poszczegolnych zmian, co 3 wartości jest kolejna dzielnica
G_min = [2 4 3 3 6 5 5 7 6]

# Maksymalna ilosc dostepnych radiowozow w dzielnicach podczas poszczegolnych zmian, co 3 wartości jest kolejna dzielnica
G_max = [3 7 5 5 7 10 8 12 10]

# Minimalna sumaryczna ilosc radiowozow dla poszczegolnych zmian
shift_min = [10, 20, 18]

# Minimalna sumaryczna ilosc radiowozow dla poszczegolnych dzielnic
district_min = [10, 14, 13]

# Macierz sąsiedztwa dla problemu
graf_matrix = [
    0 1 1 1 1 1 1 1 1 1 0
    0 0 0 0 1 1 1 0 0 0 1
    0 0 0 0 1 1 1 0 0 0 1
    0 0 0 0 1 1 1 0 0 0 1
    0 0 0 0 0 0 0 1 1 1 1
    0 0 0 0 0 0 0 1 1 1 1
    0 0 0 0 0 0 0 1 1 1 1
    0 0 0 0 0 0 0 0 0 0 1
    0 0 0 0 0 0 0 0 0 0 1
    0 0 0 0 0 0 0 0 0 0 1
    1 0 0 0 0 0 0 0 0 0 0
]

n = size(graf_matrix)[1]

# Zmienne decyzyjne
@variable(model, X[1:n, 1:n] >= 0)

# Ograniczenie na przepływy tylko po istniejących krawędziach
@constraint(model, [i = 1:n, j = 1:n; graf_matrix[i, j] == 0], X[i, j] == 0)

# Ograniczenie na zerowy balans każdego z wierzchołków
@constraint(model, [i = 1:n], sum(X[i, :]) - sum(X[:, i]) == 0)

# Zmienne decyzyjna muszą sie zawierac w przedziale wyznaczonym przez minimalne i maksymalne ilosci dostepnych radiowozow
@constraint(model, [i = 2:n-1], G_min[i-1] <= sum(X[i, :]) <= G_max[i-1])

# Ograniczenie na minimalna sumaryczna ilosc radiowozow podczas poszczegolnych zmian
@constraint(model, [i = 0:2], sum(X[:, 2 + 3*i]) + sum(X[:, 3 + 3*i]) + sum(X[:, 4 + 3*i]) >= shift_min[i+1])

# Ograniczenie na minimalna sumaryczna ilosc radiowozow w poszczegolnych dzielnicach
@constraint(model, [i = 0:2], sum(X[2 + i, :]) + sum(X[5 + i, :]) + sum(X[8 + i, :]) >= district_min[i+1])

# Funkcja celu
@objective(model, Min, X[11, 1])


