# Jakub Drzewiecki

include("ilp_model.jl")

optimize!(model)

value.(result_graph)

include("lp_model.jl")

optimize!(model)

value.(result_graph)

include("lp_nt_model.jl")

optimize!(model)

value.(result_graph)