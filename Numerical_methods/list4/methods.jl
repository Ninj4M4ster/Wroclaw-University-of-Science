# author: Jakub Drzewiecki 268418

module Methods

import Pkg
Pkg.add("Plots")
using Plots

"""
Funkcja obliczająca wartość wielomianu q_i w punkcie x_val, 
czyli iloczyn wyrażeń (x_val - x_i) dla i = 0:i-1.

@param x - wektor długości n+1 zawierający węzły x_0, ..., x_n
@param i - indeks wielomianu q_i
@param x_val - argument funkcji q_i

@return Wartość wielomianu q_i w punkcie x_val
"""
function q(x::Vector{Float64}, i::Integer, x_val::Float64)
    result = 1.0
    if(i > 1)
        for j = 1:i-1
            val = x_val - x[j]
            result *= val
        end
    end
    return result
end

"""
Funkcja obliczająca ilorazy różnicowe dla zadanych wektorów par punktów (x, y).

@param x - wektor długości n+1 zawierający węzły x_0, ..., x_n
@param f - wektor długości n+1 zawierający wartości interpolowanej funkcji w węzłach f(x_0), ..., f(x_n)

@return wektor długości n+1 zawierający obliczone ilorazy różnicowe
"""
function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})
    n = length(x)
    ilorazy = Vector{Float64}([])
    push!(ilorazy, f[1])
    for i = 2:n
        f_val = f[i]
        for j = 1:i-1
            f_val -= q(x, j, x[i]) * ilorazy[j]
        end
        q_i = q(x, i, x[i])
        new_c = f_val / q_i
        push!(ilorazy, new_c)
    end
    return ilorazy
end

"""
Funkcja obliczająca wartość wielomianu interpolacyjnego stopnia n w postaci Newtona w zadanym punkcie.

@param x - wektor długości n+1 zawierający węzły x_0, ..., x_n
@param fx - wektor długości n+1 zawierający ilorazy różnicowe 
@param t - punkt, w którym należy obliczyć wartość wielomianu

@return wartość wielomianu w punkcie t
"""
function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
    n = length(fx)
    start_value = fx[n]
    for i = n-1:-1:1
        start_value *= (t - x[i])
        start_value += fx[i]
    end
    return start_value
end

"""
Funkcja obliczająca współczynniki postaci naturalnej wielomianu interpolacyjnego.

@param x - wektor długości n+1 zawierający węzły x_0, ..., x_n
@param fx - wektor długości n+1 zawierający ilorazy różnicowe 

@return wektor długości n+1 zawierający obliczone współczynniki postaci naturalnej
"""
function naturalna(x::Vector{Float64}, fx::Vector{Float64})
    n = length(fx)
    a = Vector{Float64}(undef, n)
    a[n] = fx[n]
    for i = n-1:-1:1
        a[i] = fx[i] - a[i+1] * x[i]
        for j = i+1:n-1
            a[j] -= x[i] * a[j+1]
        end
    end
    return a
end

"""
Funkcja interpolująca zadaną funkcję w zadanym przedziale oraz przedstawiająca tą funkcję i otrzymany wielomian interpolacyjny na wykresie.

@param f - funkcja f(x) zadana jako anonimowa funkcja
@param a - lewa granica przedziału interpolacji
@param b - prawa granica przedziału interpolacji
@param n - stopień wielomianu interpolacyjnego
"""
function rysujNnfx(f,a::Float64,b::Float64,n::Int)
    x = Vector{Float64}(undef, n + 1)
    y = Vector{Float64}(undef, n + 1)
    h = (b - a) / n
    x[n + 1] = b
    y[n + 1] = f(b)
    for i = 0:n - 1
        x[i + 1] = a + i * h
        y[i + 1] = f(x[i + 1])
    end
    ilorazy = ilorazyRoznicowe(x, y)
    y_interp_fun = t -> warNewton(x, ilorazy, t)

    p = plot(y_interp_fun, a, b, label="wielomian", title="n = $n")
    p = plot!(p, f, a, b, label="funkcja")
    display(p)
end

export ilorazyRoznicowe, warNewton, naturalna, rysujNnfx

end