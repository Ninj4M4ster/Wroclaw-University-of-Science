import Pkg
Pkg.add("Plots")
using Plots

function main()
    x = collect(Float64, range(-3.0, length=1000, stop=3.0))
    y = collect(Float64, range(-3.0, length=1000, stop=3.0))
    z(x,y) = (x^2 / y^2)
    plot(x,y,z,zlimits=(-3.0, 5.0), st=:surface)
end

# Punkty osobliwe: (0, 0, 0), (0, 0, z), (0, y, 0), dla z > 0

main()