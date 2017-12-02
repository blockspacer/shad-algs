import random
n = 100000
k = random.randint(1, 100000)
q = 2 * n - 2
listik = [random.randint(1, 10 ** 9) for i in range(n)]
print(n, q, k)
print(*listik)

listus = [0 for i in range(q)]
count = 0
for i in range(q):
    if count > 0:
        num = random.randint(0, 1)
        if num == 1:
            count += 1
        else:
            count -= 1
        listus[i] = num * 'R' + (1-num) * 'L'
    else:
        listus[i] = 'R'
        count += 1
print(*listus, sep='')
