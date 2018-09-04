from math import inf
with open('input','r') as f:
    V, E = map(int, f.readline().split())
    I = f.read().splitlines()
    W = [ list(map(int, i.split())) for i in I ]

dist = [ [ inf for i in range(V) ] for j in range(V) ]

for i in range(V):
    dist[i][i] = 0

for u, v, w in W:
    dist[u - 1][v - 1] = w

for k in range(V):
    for i in range(V):
        for j in range(V):
            if dist[i][j] > dist[i][k] + dist[k][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

print("Distance Matrix is ")
print("\n".join([ " ".join(map(str, d)) for d in dist ])) 
