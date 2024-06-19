import Pkg
Pkg.add("Plots")
using Plots

function main()
    t = collect(Float64, range(-500.0, length=10000, stop=500.0))
    x = (1.0 .- t.^2) ./ (1.0 .+ t.^2)
    y = 2.0 .* t ./ (1.0 .+ t.^2)
    display(plot(x,y))

    
    x = collect(Float64, range(-1.0, length=1000, stop=1.0))
    p = plot(x -> sqrt(1.0 - x^2))
    plot!(p, x -> -sqrt(1.0 - x^2))
    display(p)
end

main()