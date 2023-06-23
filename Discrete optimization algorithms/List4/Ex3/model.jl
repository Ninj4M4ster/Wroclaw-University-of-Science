function read_file(file_name) 
    f = open(file_name, "r")

    size = parse(UInt32, readline(f))

    graph = zeros(size, size)

    while(!eof(f))
        line = split(readline(f))
        graph[parse(UInt32, line[1]) + 1, parse(UInt32, line[2]) + 1] = parse(Float64, line[3])
    end

    close(f)

    return graph
end

graph = read_file("./cube_graph.txt")
println("Graph read")
n = size(graph)[1]

import Pkg
Pkg.add("JuMP")
import Pkg
Pkg.add("GLPK")

using JuMP
using GLPK

model = Model(GLPK.Optimizer)

@variable(model, X[1:n, 1:n] >= 0)

@constraint(model, [i = 1:n, j = 1:n], X[i,j] <= graph[i,j])

@constraint(model, [i = 1:n; i != 1 && i != n], sum(X[i, :]) == sum(X[:,i]))

@objective(model, Max, sum(X[1, :]))

optimize!(model)

println(objective_value(model))

