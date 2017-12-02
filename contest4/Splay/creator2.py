n = 100000
print(n)
for i in range(n // 2):
    print(i, i, 2 * n // 2 - 1 - i, 2 * n // 2 - 1 - i)
for i in range(n // 2):
    print(i, -i - 1, 2 * n // 2 - 1 - i, -(2 * n // 2 - 1 - i) - 1)
