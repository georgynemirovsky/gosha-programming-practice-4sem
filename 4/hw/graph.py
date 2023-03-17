import json
import matplotlib.pyplot as plt

x = []
y = []
with open('times.json') as json_file:
    data = json.load(json_file)

num_of_threads = data['num_of_threads']
for i in range(num_of_threads):
    x.append(i + 1)
    y.append(data[str(i + 1)])
5

fig, ax = plt.subplots()
plt.suptitle("")
ax.plot(x, y, marker='.', markersize=10)
ax.set_ylabel("time")
ax.set_xlabel("number of threads")
plt.show()