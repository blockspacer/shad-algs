import random
n = random.randint(1, 10000)
k = random.randint(1, n)
print(n, k)
for i in range(n):
    print(random.uniform(-1000.0, 1000.0), random.uniform(-1000.0, 1000.0))

