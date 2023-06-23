import matplotlib.pyplot as plt
from subprocess import Popen, PIPE


def readFile(file_name):
    data = []
    with open(file_name, "r") as f:
        line = f.readline().split(";")
        data.append(float(line[0]))
        data.append(float(line[1]))
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

    print("Starting test for max flows")
    for k in range(3, 11):
        final_flows = []
        for i in range(1, k+1):
            flows = []
            for j in range(N):
                process = Popen(["zad2.exe", str(k), str(i), "1"],
                                stdin=PIPE,
                                stdout=PIPE,
                                stderr=PIPE)
                out, err = process.communicate()

                data = readFile("zad2.txt")
                flows.append(data[0])
            final_flows.append(sum(flows) / float(N))

        # wykres przeplywu w zaleznosci od i
        I = [l for l in range(1, k+1)]
        saveGraph(f'Max flows, k={k}', f'max_flow_k_{k}', I, final_flows)
        print(f'{k} number finished')

    print("Starting test for time")
    for i in range(1, 11):
        final_times = []
        for k in range(3, 11):
            if k < i:
                continue
            times = []
            for j in range(N):
                process = Popen(["zad2.exe", str(k), str(i), "1"],
                                stdin=PIPE,
                                stdout=PIPE,
                                stderr=PIPE)
                out, err = process.communicate()

                data = readFile("zad2.txt")
                times.append(data[1])
            final_times.append(sum(times) / float(N))
        # wykres czasu w zaleznosci od k
        K = [k for k in range(3, 11)]
        saveGraph(f'Times, i={i}', f'time_i_{i}', K, final_times)
        print(f'{i} number finished')


if __name__ == '__main__':
    main()
