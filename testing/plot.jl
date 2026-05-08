using Graphs
using GLMakie
using GraphMakie
using Makie
using Colors
using MatrixMarket

A = MatrixMarket.mmread(ARGS[1])
g = SimpleGraph(A)
partition = [parse(Int, ss) for ss in split(readlines("results/result.txt")[1])]

f, ax, p  = graphplot(g, node_color = partition)

display(f)
