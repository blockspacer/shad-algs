import random
m = random.randint(1, 100000)
listik = [random.randint(1, 2 ** 31 - 1) for i in range(m)]
print(len(listik))
print(*listik)
