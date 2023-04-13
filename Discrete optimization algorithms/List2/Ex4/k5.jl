include("model.jl")

k = 5
# Kazdy kontener musi byc monitorowany przez co najmniej jedna kamere
@constraint(model, [i = 1:n, j = 1:m; map[i, j] == 1], sum(cameras[x, y] for x = i-k:i+k, y = j-k:j+k if 1 <= x <= n && 1 <= y <= m) >= 1)