import Pkg
Pkg.add("Gadfly")
using Gadfly

function main()
    pol_one = layer(z=(x,y) -> (x*x + y*y + 4*y)^2 - 16 * (x^2 + y^2),
    xmin=[-10], xmax=[10], ymin=[5], ymax=[-10],
    Geom.contour(levels=[0;]))
    points_one = layer(x=[-1.732050, 1.732050, 5.1961524, -5.1961524], y=[1.0, 1.0, -3.0, -3.0], Geom.point)

    pol_two = layer(z=(x,y) -> (2.0 * (x^2.0 + 9.0) * (y^2.0-16.0) + (x^2 - 9.0)^2 + (y^2.0-16.0)^2),
    xmin=[-10], xmax=[10], ymin=[5], ymax=[-10],
    Geom.contour(levels=[0;]))
    points_two = layer(x=[0.0, 0.0, -3.0, -3.0, 3.0, 3.0], y=[2.64575, -2.64575, 4.0, -4.0, 4.0, -4.0], Geom.point)

    pol_three = layer(z=(x,y) -> (350.0 * x^2 * y^2 - 15.0^2 * (x^2+y^2) + 12.0^2 * (x^4 + y^4) + 81.0),
    xmin=[-2], xmax=[2], ymin=[2], ymax=[-2],
    Geom.contour(levels=[0;]))
    points_three = layer(x=[-0.4445, -0.4445, 0.4445, 0.4445, -0.71252, -0.71252, 0.71252, 0.71252, -0.40529, -0.40529, 0.40529, 0.40529, -0.73557, -0.73557, 0.73557, 0.73557], y=[0.73557, -0.73557, 0.73557, -0.73557, 0.40529, -0.40529, 0.40529, -0.40529, 0.7125251, -0.7125251, 0.7125251, -0.7125251, 0.444563, -0.444563, 0.444563, -0.444563], Geom.point)

    display(plot(pol_one, points_one, Guide.xlabel("x"), Guide.ylabel("y")))
    display(plot(pol_two, points_two, Guide.xlabel("x"), Guide.ylabel("y")))
    display(plot(pol_three, points_three, Guide.xlabel("x"), Guide.ylabel("y")))
    
    
               
end

main()