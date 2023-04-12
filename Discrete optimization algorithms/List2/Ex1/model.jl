import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("Clp")

using JuMP
using Clp

model = Model(Clp.Optimizer)

@variable(model, 0 <= x1 <= 275000)
@variable(model, 0 <= x2 <= 550000)
@variable(model, 0 <= x3 <= 660000)

@variable(model, y1 >= 110000)
@variable(model, y2 >= 220000)
@variable(model, y3 >= 330000)
@variable(model, y4 >= 440000)

@objective(model, Min, 40*x1 + 43*x2 + 35*x3)

@constraint(model, c1, y1 + y2 + y3 + y4 == x1 + x2 + x3)