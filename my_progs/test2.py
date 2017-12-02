import random
listik = [random.randint(-(2 ** 31), 2 ** 31 - 1) for i in range(100000)]
print(*listik)
