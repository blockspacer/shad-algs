import random
n = 50000
m = 50000
listik = []
print("starting")
for i in range(n - 1):
    listik.append((i + 1, i + 2))
print(n, m, sep= ' ')
for i in range(n - 1):
    print(listik[i][0], listik[i][1], random.randint(1, 5), sep= ' ')
