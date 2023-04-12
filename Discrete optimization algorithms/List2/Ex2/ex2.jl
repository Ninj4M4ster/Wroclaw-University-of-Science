include("ilp_model.jl")

optimize!(model)

value.(result_graph)
