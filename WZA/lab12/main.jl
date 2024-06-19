import Pkg
Pkg.add("Plots")
using Plots

function main()
    a_vals = [-4.0, -2.0, 0.0, 1.0, 2.0, 3.0]
    t = collect(Float64, range(-10.0, length=500, stop=10.0))
    for a in a_vals
        if(a == 0.0)
            t = collect(Float64, range(-100.0, length=50, stop=100.0))
            r = 1.0 ./ cos.(t) .+ a .* cos.(t)
            x = r .* cos.(t)
            y = r .* sin.(t)
            display(plot(x, y, title=a, ylimits=(-100.0, 100.0)))
        else
            t = collect(Float64, range(-10.0, length=500, stop=10.0))
            r = 1.0 ./ cos.(t) .+ a .* cos.(t)
            x = r .* cos.(t)
            y = r .* sin.(t)
            display(plot(x, y, title=a, ylimits=(-10.0, 10.0)))
        end
    end
end

main()