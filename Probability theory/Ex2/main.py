import time

import matplotlib as pyplot
import numpy as np
import multiprocessing
import random

MAX_NUMBER_OF_POINTS: int = 100000
ITERATION_STEP: int = 1000
K: int = 50
M_SCALE: int = 1


def check_b(quantities_flags: dict,
            magnitudes_strings: multiprocessing.Queue,
            urns: list,
            n: int):
    for i in range(len(urns)):
        if urns[i] > 1:
            quantities_flags['b_found'] = True
            magnitudes_strings.put(str(n) + " b " + str(i))


def check_c(quantities_flags: dict,
            magnitudes_strings: multiprocessing.Queue,
            urns: list,
            n: int,
            number_of_throws: int):
    i = 0
    while i < len(urns) and urns[i] >= 1:
        i += 1
        continue
    if i == len(urns):
        quantities_flags['c_found'] = True
        magnitudes_strings.put(str(n) + " c " + str(number_of_throws))


def check_d(quantities_flags: dict,
            magnitudes_strings: multiprocessing.Queue,
            urns: list,
            n: int,
            number_of_throws: int):
    i = 0
    while i < len(urns) and urns[i] >= 2:
        i += 1
        continue
    if i == len(urns):
        quantities_flags['d_found'] = True
        magnitudes_strings.put(str(n) + " d " + str(number_of_throws))


def check_u(urns: list,
            n: int,
            magnitude_strings: multiprocessing.Queue):
    counter = 0
    for i in range(len(urns)):
        if urns[i] == 0:
            counter += 1
    magnitude_strings.put(str(n) + " u " + str(counter))


def check_l(urns: list,
            n: int,
            magnitude_strings: multiprocessing.Queue):
    magnitude_strings.put(str(n) + " l " + str(max(urns)))


def check_quantities(quantities_flags: dict,
                     magnitudes_strings: multiprocessing.Queue,
                     urns: list,
                     n: int,
                     number_of_throws: int):
    if not quantities_flags['b_found']:
        check_b(quantities_flags, magnitudes_strings, urns, n)
    if not quantities_flags['c_found']:
        check_c(quantities_flags, magnitudes_strings, urns, n, number_of_throws)
    if not quantities_flags['d_found']:
        check_d(quantities_flags, magnitudes_strings, urns, n, number_of_throws)


def spread_spheres_in_urns(n: int,
                           magnitudes_strings: multiprocessing.Queue,
                           rand_gen: random.SystemRandom):
    urns = [0] * n
    number_of_throws = 0
    quantities_flags = {"b_found": False,
                        "c_found": False,
                        "d_found": False}
    while True:
        if quantities_flags['d_found']:
            break
        urns[rand_gen.randint(0, n - 1)] += 1
        number_of_throws += 1
        check_quantities(quantities_flags, magnitudes_strings, urns, n, number_of_throws)
        if number_of_throws == n:
            check_u(urns, n, magnitudes_strings)
            check_l(urns, n, magnitudes_strings)


def generate_experiment_in_range(left: int,
                                 right: int,
                                 magnitudes_strings: multiprocessing.Queue,
                                 rand_gen: random.SystemRandom):
    for n in range(left, right, ITERATION_STEP):
        print(n)
        for j in range(K):
            spread_spheres_in_urns(n, magnitudes_strings, rand_gen)
            print(n)


def main():
    rand_gen = random.SystemRandom()
    cpu_count: int = multiprocessing.cpu_count()
    points_per_process: int = MAX_NUMBER_OF_POINTS // cpu_count
    reminder: int = MAX_NUMBER_OF_POINTS % cpu_count
    current_left = 1000
    processes = []

    magnitudes_strings = multiprocessing.Queue()
    for i in range(cpu_count):
        if i == cpu_count - 1:
            # processes.append(multiprocessing.Process(target=generate_experiment_in_range,
            #                           args=(current_left,
            #                                 current_left + points_per_process + reminder + ITERATION_STEP,
            #                                 magnitudes_strings,
            #                                 rand_gen)))
            generate_experiment_in_range(current_left, current_left + points_per_process + reminder + ITERATION_STEP, magnitudes_strings, rand_gen)
        else:
            # processes.append(multiprocessing.Process(target=generate_experiment_in_range,
            #                  args=(current_left,
            #                        current_left + points_per_process,
            #                        magnitudes_strings,
            #                        rand_gen)))
            generate_experiment_in_range(current_left, current_left + points_per_process, magnitudes_strings, rand_gen)
        current_left += points_per_process

    for proces in processes:
        proces.start()

    for proces in processes:
        proces.join()

    while not magnitudes_strings.empty():
        print(magnitudes_strings.get())


if __name__ == '__main__':
    start = time.perf_counter()
    main()
    end = time.perf_counter()
    print(end - start)
