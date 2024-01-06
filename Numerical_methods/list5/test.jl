# author: Jakub Drzewiecki, 268418

include("matrixgen.jl")
include("blocksys.jl")
using Main.blocksys
using .matrixgen
import Pkg
Pkg.add("Plots")
using Plots

function paste_sparse_matrix(indexes_pairs::Vector{Vector{Int64}}, values::Vector{Float64}, size::Int64)
    matrix = Dict{Int64, Dict{Int64, Float64}}()
    max_rows_indexes = zeros(Int64, size)
    for i = 1:size
        matrix[i] = Dict{Int64, Float64}()
    end

    for i in eachindex(indexes_pairs)
        ind = indexes_pairs[i]
        matrix[ind[1]][ind[2]] = values[i]
        if(max_rows_indexes[ind[2]] < ind[1])
            max_rows_indexes[ind[2]] = ind[1]
        end
    end
    return SMatrix(matrix, max_rows_indexes, size)
end

function paste_normal_matrix(indexes_pairs::Vector{Vector{Int64}}, values::Vector{Float64}, size::Int64)
    A = zeros(Float64, size, size)
    for i in eachindex(indexes_pairs)
        ind = indexes_pairs[i]
        A[ind[1], ind[2]] = values[i]
    end
    return A
end

function find_normal_result(A::Matrix{Float64}, b::Vector{Float64})
    return A\b
end

function findLuAndSolve(A::SMatrix, b::Vector{Float64})
    LU = luDistribution(A)
    return solveWithLU(LU, b)
end

function findLuPivotedAndSolve(A::SMatrix, b::Vector{Float64})
    LU, pivots = luDistributionPartialChoice(A)
    return solveWithPivotedLU(LU, b, pivots)
end

function find_error(x)
    x_original = ones(length(x))
    return sum(abs.(abs.(x) - abs.(x_original))) / length(x)
end

struct Sol
    times::Vector{Float64}
    mem::Vector{Float64}
    error::Vector{Vector{Float64}}
end

function main() 
    functions = [gaussElimination, gaussEliminationPartialChoice, findLuAndSolve, findLuPivotedAndSolve]
    final_solutions = [Sol(zeros(Float64, 0), zeros(Int, 0), [Vector{Float64}(undef, 100) for _ = 1:6]) for _ = 1:5]
    iter = 1
    for i = 1000:1000:100000
        solutions = [Sol(zeros(Float64, 0), zeros(Int, 0),  [Vector{Float64}(undef, 1) for _ = 1:6]) for _ = 1:5]
        c_index = 1
        for c in [1.0, 10.0, 10.0^3, 10.0^7, 10.0^12, 10.0^16]
            indexes, vals = blockmat(i, 5, c, "")
            A_spar = paste_sparse_matrix(indexes, vals, i)
            A_normal = paste_normal_matrix(indexes, vals, i)
            b = generateRightSideVector(A_spar)

            stats_normal = @timed find_normal_result(A_normal, b)
            res = find_normal_result(A_normal, b)
            k = 1
            append!(solutions[k].times, stats_normal.time)
            append!(solutions[k].mem, stats_normal.bytes)
            solutions[k].error[c_index][1] = find_error(res)
            for f in functions
                k += 1
                A_copy = deepcopy(A_spar)
                b_copy = deepcopy(b)
                stats = @timed f(A_copy, b_copy)
                res = f(A_copy, b_copy)
                
                append!(solutions[k].times, stats.time)
                append!(solutions[k].mem, stats.bytes)
                solutions[k].error[c_index][1] = find_error(res)
            end
            c_index += 1
        end
        for k = 1:5
            append!(final_solutions[k].times, sum(solutions[k].times) / length(solutions[k].times))
            append!(final_solutions[k].mem, sum(solutions[k].mem) / length(solutions[k].mem))
            for l = 1:6
                final_solutions[k].error[l][iter] = solutions[k].error[l][1]
            end
        end
        println(i)
        iter += 1
    end

    x_ax = 1000:1000:100000

    plot(
        x_ax, 
        [final_solutions[i].times for i in 1:5], 
        title="Złożoność czasowa algorytmów (sekundy)", 
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("times.png")

    plot(
        x_ax, 
        [final_solutions[k].times for k in 2:length(final_solutions)], 
        title="Złożoność czasowa algorytmów (sekundy)", 
        legend=:topleft,
        label=["Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("times2.png")

    plot(
        x_ax, 
        [final_solutions[i].mem for i in 1:5], 
        title="Zużycie pamięci", 
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
        )
    savefig("mem.png")

    plot(
        x_ax, 
        [final_solutions[k].mem for k in 2:length(final_solutions)], 
        title="Zużycie pamięci", 
        legend=:topleft,
        label=["Gauss" "Gauss z wyborem" "LU" "LU z wyborem"])
    savefig("mem2.png")

    plot(
        x_ax,
        [final_solutions[k].error[1] for k in 1:5],
        title="Błąd względny uzyskanego wyniku dla c = 1",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("error1.png")

    plot(
        x_ax,
        [final_solutions[k].error[1] for k in 1:3],
        title="Błąd względny uzyskanego wyniku dla c = 1",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem"]
    )
    savefig("error1_no_lu.png")

    plot(
        x_ax,
        [final_solutions[k].error[2] for k in 1:5],
        title="Błąd względny uzyskanego wyniku dla c = 10",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("error2.png")
    plot(
        x_ax,
        [final_solutions[k].error[2] for k in 1:3],
        title="Błąd względny uzyskanego wyniku dla c = 10",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem"]
    )
    savefig("error2_no_lu.png")

    plot(
        x_ax,
        [final_solutions[k].error[3] for k in 1:5],
        title="Błąd względny uzyskanego wyniku dla c = 10^3",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("error3.png")

    plot(
        x_ax,
        [final_solutions[k].error[3] for k in 1:3],
        title="Błąd względny uzyskanego wyniku dla c = 10^3",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem"]
    )
    savefig("error3_no_lu.png")

    plot(
        x_ax,
        [final_solutions[k].error[4] for k in 1:5],
        title="Błąd względny uzyskanego wyniku dla c = 10^7",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("error4.png")

    plot(
        x_ax,
        [final_solutions[k].error[4] for k in 1:3],
        title="Błąd względny uzyskanego wyniku dla c = 10^7",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem"]
    )
    savefig("error4_no_lu.png")

    plot(
        x_ax,
        [final_solutions[k].error[5] for k in 1:5],
        title="Błąd względny uzyskanego wyniku dla c = 10^12",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("error5.png")

    plot(
        x_ax,
        [final_solutions[k].error[5] for k in 1:3],
        title="Błąd względny uzyskanego wyniku dla c = 10^12",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem"]
    )
    savefig("error5_no_lu.png")

    plot(
        x_ax,
        [final_solutions[k].error[6] for k in 1:5],
        title="Błąd względny uzyskanego wyniku dla c = 10^16",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem" "LU" "LU z wyborem"]
    )
    savefig("error6.png")

    plot(
        x_ax,
        [final_solutions[k].error[6] for k in 1:3],
        title="Błąd względny uzyskanego wyniku dla c = 10^16",
        legend=:topleft,
        label=["Metoda tradycyjna" "Gauss" "Gauss z wyborem"]
    )
    savefig("error6_no_lu.png")
end

main()
