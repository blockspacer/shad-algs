import random

def brace(num):
    if num == 0:
        return "("
    elif num == 1:
        return "["
    elif num == 2:
        return "{"
    elif num == 3:
        return ")"
    elif num == 4:
        return "]"
    elif num == 5:
        return "}"

#print(*[brace(random.randint(0, 5)) for i in range(1000000)], sep='')
res = []
for i in range(50000):
    dec = random.randint(0, 2)
    if dec == 0:
        dec2 = random.randint(0, 2)
        res.append(brace(dec2))
        res.append(brace(dec2 + 3))
    elif dec == 1:
        dec2 = random.randint(0, 2)
        res.insert(0, brace(dec2))
        res.append(brace(dec2 + 3))
    elif dec == 2:
        dec2 = random.randint(0, 2)
        res.insert(0, brace(dec2 + 3))
        res.insert(0, brace(dec2))
print(*res, sep='')
#print(brace(3))