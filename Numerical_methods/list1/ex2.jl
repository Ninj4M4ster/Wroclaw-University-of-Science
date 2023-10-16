# author: Jakub Drzewiecki 268418

function macheps(t)
    return t(3) * (t(4)/t(3) - t(1)) - t(1)
end

eps(Float64)
# macheps(Float64)