import random

n = random.randint(1, 2000)
m = random.randint(1, 2000)
print(n, m)
for i in range(n):
    listik = [random.randint(-(2 ** 31), 2 ** 31 - 1) for j in range(m)]
    listik.sort()
    print(*listik)
