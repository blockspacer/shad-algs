import random
print(100000)

listik = [i for i in range(100000)]

print(*listik)

print(1000000)

listik = [random.randint(-(10 ** 4), 10 ** 4) for i in range(1000000)]

print(*listik)
