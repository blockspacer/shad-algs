import random
n = 1000000
listik = [(2 * (i + 1),2 * (i + 1), 2 * (i + 1)) for i in range(n)]
print(n)
for i in range(n):
    print(*listik[i])
