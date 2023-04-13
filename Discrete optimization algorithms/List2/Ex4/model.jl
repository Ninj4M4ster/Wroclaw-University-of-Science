import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("HiGHS")
import Pkg

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

map = [
    1 0 0 0 0 0 0 0 0
    0 0 1 0 0 0 0 0 1
    0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 1 0 0
    0 0 0 0 0 0 0 0 0
    1 0 0 0 1 0 0 0 0
    0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 1
    0 0 1 0 0 0 0 0 0
    0 0 0 0 0 0 1 0 0
    0 1 0 0 0 0 0 0 1
]

n = size(map)[1]
m = size(map)[2]

# Mapa z umieszczeniem kamer
@variable(model, cameras[1:n, 1:m], Bin)
# Uniemozliwienie umieszczenia kamer w miejscu, w ktorym znajduje sie kontener
@constraint(model, [i = 1:n, j = 1:m; map[i, j] == 1], cameras[i, j] == 0)
# Optymalizacja ilosci kamer
@objective(model, Min, sum(cameras[:, :]))
