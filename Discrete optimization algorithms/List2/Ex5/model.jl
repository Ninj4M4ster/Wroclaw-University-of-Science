import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("Clp")

using JuMP
using Clp

model = Model(Clp.Optimizer)

# Czas obrobki materialow
machines_times = [
    5 10 6
    3 6 4
    4 5 3
    4 2 1
]

# Ceny sprzedazy materialow
materials_sell_cost = [
    9 7 6 5
]

# Koszty materialowe
materials_buy_cost = [
    4 1 1 1
]

# Finalny zysk ze sprzedazy materialow
materials_final_sell_cost = materials_sell_cost .- materials_buy_cost

# Koszt godziny pracy maszyn
machines_hour_work_cost = [
    2, 2, 3
]

# Maksymalny popyt materialow
materials_max_demand = [
    400 100 150 500
]


# Zmienne decyzyjne
@variable(model, 0 <= p1 <= materials_max_demand[1])
@variable(model, 0 <= p2 <= materials_max_demand[2])
@variable(model, 0 <= p3 <= materials_max_demand[3])
@variable(model, 0 <= p4 <= materials_max_demand[4])

# Zmienne dla czasu pracy kazdej z maszyn
m1 = machines_times[1, 1] * p1 + machines_times[2, 1] * p2 + machines_times[3, 1] * p3 + machines_times[4, 1] * p4
m2 = machines_times[1, 2] * p1 + machines_times[2, 2] * p2 + machines_times[3, 2] * p3 + machines_times[4, 2] * p4
m3 = machines_times[1, 3] * p1 + machines_times[2, 3] * p2 + machines_times[3, 3] * p3 + machines_times[4, 3] * p4

# Ograniczenie pracy nad materialami
@constraint(model, 0 <= m1 <= 3600)
@constraint(model, 0 <= m2 <= 3600)
@constraint(model, 0 <= m3 <= 3600)

# Cel optymalizacji
@objective(model, Max, materials_final_sell_cost[1] * p1 
 + materials_final_sell_cost[2] * p2 
 + materials_final_sell_cost[3] * p3 
 + materials_final_sell_cost[4] * p4 
 - machines_hour_work_cost[1] / 60 * m1 
 - machines_hour_work_cost[2] / 60 * m2 
 - machines_hour_work_cost[3] / 60 * m3)