include("k1.jl")

optimize!(model)

result1 = cameras

include("k3.jl")

optimize!(model)

result2 = cameras

value.(cameras)

include("k5.jl")

optimize!(model)

result3 = cameras

println("Wynik dla k = 1")
for i = 1:n
    for j = 1:m
        print(value(result1[i, j]))
        print(" ")
    end
    print("\n")
end

println("\nWynik dla k = 3")

for i = 1:n
    for j = 1:m
        print(value(result2[i, j]))
        print(" ")
    end
    print("\n")
end

println("\nWynik dla k = 5")

for i = 1:n
    for j = 1:m
        print(value(result3[i, j]))
        print(" ")
    end
    print("\n")
end