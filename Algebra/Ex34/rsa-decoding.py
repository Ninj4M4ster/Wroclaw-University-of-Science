with open("text.txt", "r") as file:
    data = [int(string, base=16) for string in file.read().split(':')]

n = 101080891
d = [int(index) for index in bin(2062465).lstrip('0b')]

results = []

for i in range(len(data)):
    bases = [data[i] % n]
    results.append(bases[0] if d[len(d)-1] == 1 else 1)
    for j in range(1, len(d)):
        bases.append((bases[j-1] * bases[j-1]) % n)
        if d[len(d) - 1 - j]:
            results[i] *= bases[j]
    results[i] = results[i] % n

decoded = []

for result in results:
    decoded.append(chr(result))

print(''.join(decoded))
