from math import inf
s1 = input()
s2 = input()

dp = [ [ -inf for i in range(len(s2) + 1) ] for j in range(len(s1) + 1) ]
b = [ [ -1 for i in range(len(s2) + 1) ] for j in range(len(s1) + 1) ]

for i in range(len(s2) + 1):
    dp[0][i] = 0

for i in range(len(s1) + 1):
    dp[i][0] = 0

for i in range(1, len(s1) + 1):
    for j in range(1, len(s2) + 1):
        if s1[i - 1] == s2[j - 1]:
            dp[i][j] = 1 + dp[i - 1][j - 1]
            b[i][j] = 1
        else:
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
            if dp[i][j] == dp[i - 1][j]:
                b[i][j] = 2
            else:
                b[i][j] = 3

print(dp[len(s1)][len(s2)])

def printLCS(i, j):
    subsequence = ""
    while i!=0 or j!=0 :
        if b[i][j]==1:
            subsequence += s1[i-1]
            i -= 1
            j -= 1
        else:
            if b[i][j] == 2:
                i -= 1
            else:
                j -= 1
    print(subsequence[::-1])

printLCS(len(s1), len(s2))



