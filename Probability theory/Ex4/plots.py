import math

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from collections import Counter

graph_name = "lollipop"

matplotlib.rcParams["figure.dpi"] = 100
x = np.arange(100, 2050, 50)

plt.axvline(x=0, color="black")
plt.axhline(y=0, color="black")
plt.title(f"{graph_name} graph")
current_x = 100
sums = Counter()
with open(f"../../{graph_name}.txt") as clique_file:
    for line in clique_file:
        if line.startswith("x"):
            continue
        data = line.split(";")
        n = int(data[0])
        value = int(data[1])
        sums[n] += value
        plt.scatter(n, value, s=1.5, color="blue")

y = np.array([])
means = np.array([])
for total in sums.values():
    means = np.append(means, float(total / 16.0))
    y = np.append(y, float(total / 16.0))

plt.plot(x, y, color="orange")

plt.show()

# find asymptotic
plt.clf()

plt.title(f"{graph_name}/n")
plt.axvline(x=0, color="black")
plt.axhline(y=0, color="black")

On = np.array([])
j = 0
for i in range(100, 2050, 50):
    On = np.append(On, float(means[j] / i))
    j += 1

plt.plot(x, On, color="blue")

plt.show()

plt.clf()

plt.title(f"{graph_name}/nlogn")
plt.axvline(x=0, color="black")
plt.axhline(y=0, color="black")

Onlogn = np.array([])
j = 0
for i in range(100, 2050, 50):
    Onlogn = np.append(Onlogn, float(means[j] / (i * math.log(i))))
    j += 1

plt.plot(x, Onlogn, color="blue")

plt.show()

plt.clf()

plt.title(f"{graph_name}/n^2")
plt.axvline(x=0, color="black")
plt.axhline(y=0, color="black")

Onn = np.array([])
j = 0
for i in range(100, 2050, 50):
    Onn = np.append(Onn, float(means[j] / (i * i)))
    j += 1

plt.plot(x, Onn, color="blue")

plt.show()

plt.clf()


plt.clf()

plt.title(f"{graph_name}/n^3")
plt.axvline(x=0, color="black")
plt.axhline(y=0, color="black")

Onnn = np.array([])
j = 0
for i in range(100, 2050, 50):
    Onnn = np.append(Onnn, float(means[j] / (i * i * i)))
    j += 1

plt.plot(x, Onnn, color="blue")

plt.show()
