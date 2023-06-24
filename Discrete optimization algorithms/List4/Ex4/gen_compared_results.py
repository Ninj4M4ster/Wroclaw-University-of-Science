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
              y_ax,
              y_ax_2,
              upper_right):
    plt.title(graph_name)
    plt.plot(x_ax, y_ax, label="dynic")
    plt.plot(x_ax, y_ax_2, label="edmonds-karp", color="orange")

    if upper_right:
        plt.figlegend(loc="upper right")
    else:
        plt.figlegend(loc="upper left")

    plt.savefig(file_name)
    plt.clf()


def main():
    N = 50

    final_flows_edm = []
    final_times_edm = []
    final_paths_count_edm = []
    final_flows_dynic = []
    final_times_dynic = []
    final_paths_count_dynic = []
    for i in range(16):
        flows = []
        times = []
        paths_count = []
        for j in range(N):
            process = Popen(["zad4.exe", str(i + 1), "1"],
                            stdin=PIPE,
                            stdout=PIPE,
                            stderr=PIPE)
            out, err = process.communicate()

            data = readFile("zad4.txt")
            flows.append(data[0])
            times.append(data[1])
            paths_count.append(data[2])
        final_flows_dynic.append(sum(flows) / float(N))
        final_times_dynic.append(sum(times) / float(N))
        final_paths_count_dynic.append(sum(paths_count) / float(N))

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
        final_flows_edm.append(sum(flows) / float(N))
        final_times_edm.append(sum(times) / float(N))
        final_paths_count_edm.append(sum(paths_count) / float(N))
        print(f'Finished {i}')

    K = [k + 1 for k in range(16)]
    saveGraph("Max flows", "max_flow", K, final_flows_dynic, final_flows_edm, True)
    saveGraph("Time", "time", K, final_times_dynic, final_times_edm, False)
    saveGraph("Paths count", "paths_count", K, final_paths_count_dynic, final_paths_count_edm, False)


if __name__ == '__main__':
    main()
