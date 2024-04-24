function isPointLowerEqual(point_l::Vector{Float64}, point_r::Vector{Float64})
    for i = eachindex(point_l)
        if(point_l[i] > point_r[i])
            return false
        end
    end
    return true
end

function isPointLarger(point_l::Vector{Float64}, point_r::Vector{Float64})
    for i = eachindex(point_l)
        if(point_l[i] <= point_r[i])
            return false
        end
    end
    return true
end

function findMinPoints(points::Vector{Vector{Float64}})
    min_points_set = [points[1]]
    for i = 2:length(points)
        point_lower = true
        new_min_points_set = []
        for j = eachindex(min_points_set)
            copy_to_new_set = true
            if(isPointLowerEqual(points[i], min_points_set[j]))
                copy_to_new_set = false
            elseif(isPointLarger(points[i], min_points_set[j]))
                point_lower = false
            end
            if(copy_to_new_set)
                push!(new_min_points_set, min_points_set[j])
            end
        end
        min_points_set = new_min_points_set
        if(point_lower)
            push!(min_points_set, points[i])
        end
    end
    return min_points_set
end

function main()
    points = [[0.1, 0.5, 0.3], [0.2, 0.6, 0.8], [0.0, 0.6, 0.4], [0.8, -0.2, 1.3], [-1.0, -2.0, -3.0], [-2.0, -1.0, -4.0]]
    findMinPoints(points)
end

main()