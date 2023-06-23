import matplotlib.pyplot as plt
from subprocess import Popen, PIPE


def readFile(file_name):
    data = []
    with open(file_name, "r") as f:
        line = f.readline().split(";")
        data.append(float(line[0]))
        data.append(float(line[1]))
        data.append(float(line[2]))
    return data


def saveGraph(graph_name,
              file_name,
              x_ax,
              y_ax):
    plt.title(graph_name)
    plt.plot(x_ax, y_ax)

    plt.savefig(file_name)
    plt.clf()


def main():
    N = 50

    final_flows = []
    final_times = []
    final_paths_count = []
    for i in range(16):
        flows = []
        times = []
        paths_count = []
        for j in range(N):
            process = Popen(["zad1.exe", str(i + 1), "1"],
                            stdin=PIPE,
                            stdout=PIPE,
                            stderr=PIPE)
            out, err = process.communicate()

            data = readFile("zad1.txt")
            flows.append(data[0])
            times.append(data[1])
            paths_count.append(data[2])
        final_flows.append(sum(flows) / float(N))
        final_times.append(sum(times) / float(N))
        final_paths_count.append(sum(paths_count) / float(N))

    K = [k + 1 for k in range(16)]
    saveGraph("Max flows", "max_flow", K, final_flows)
    saveGraph("Time", "time", K, final_times)
    saveGraph("Paths count", "paths_count", K, final_paths_count)


if __name__ == '__main__':
    main()
