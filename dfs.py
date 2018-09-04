from math import inf
with open('input','r') as f:
    V, E = map(int, f.readline().split())
    I = f.read().splitlines()
    W = [ list(map(int, i.split())) for i in I ]

adjMatrix = [ [ 0 for i in range(V) ] for j in range(V) ]
color = [ 'W' for i in range(V) ]
discoverTime = [ -1 ] * V
finishTime = [ -1 ] * V

for i in range(V):
    adjMatrix[i][i] = 0

for u, v in W:
    adjMatrix[u][v] = 1
time = 0

def dfs(v):
    global time
    time += 1
    discoverTime[v] = time
    color[v] = 'G'
    for i in range(V):
        if adjMatrix[v][i]==1 and color[i] == 'W':
            dfs(i)
    time += 1
    finishTime[v] = time
    color[v] = 'B'

for i in range(V):
    if color[i]=='W':
        dfs(i)
        
print("Vertex :")
print(" ".join([ str(i) for i in range(V)]))
print("Discover Time : ")
print(" ".join([ str(discoverTime[i]) for i in range(V)]))
print("Finish Time : ")
print(" ".join([ str(finishTime[i]) for i in range(V)]))
