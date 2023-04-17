# Jakub Drzewiecki

import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

# Koszty paliw wybranej firmy na kazdym z lotnisk
costs = [
    10 7 8
    10 11 14
    9 12 4
    11 13 9
]

n = size(costs)[1]
m = size(costs)[2]

# Zapotrzebowanie na paliwo na poszczegolnych lotniskach
needed_fuel_ammount = [110000 220000 330000 440000]

# Paliwo dostepne u kazdego z dostawcow
available_fuel = [275000 550000 660000]

# Macierz zmiennych decyzyjnych
@variable(model, X[1:n, 1:m] >= 0)

# Ograniczenia na dostepne paliwo
@constraint(model, sum(X[:, 1]) <= available_fuel[1])
@constraint(model, sum(X[:, 2]) <= available_fuel[2])
@constraint(model, sum(X[:, 3]) <= available_fuel[3])

# Ograniczenia na zapotrzebowanie na paliwo na poszczegolnych lotniskach
@constraint(model, needed_fuel_ammount[1] == sum(X[1, :]))
@constraint(model, needed_fuel_ammount[2] == sum(X[2, :]))
@constraint(model, needed_fuel_ammount[3] == sum(X[3, :]))
@constraint(model, needed_fuel_ammount[4] == sum(X[4, :]))

# Funkcja celu
@objective(model, Min, sum(X .* costs))
