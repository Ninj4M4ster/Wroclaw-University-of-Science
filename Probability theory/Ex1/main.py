import random
import math

import matplotlib
import matplotlib.pyplot as plot
import numpy as np


class Point:
    """
    Class representing a point on 2D space.
    """
    x_: float
    y_: float

    def __init__(self,
                 a: float,
                 b: float,
                 M: float = None,
                 rand_gen: random.SystemRandom = None,
                 randomize: bool = True):
        """
        Initialization. If randomize is true, it creates a point in random place
        considering given limits.
        Else it creates a point in x = a and y = b.

        :param a: Left limit or x position.
        :param b: Right limit or y position.
        :param M: Upper bound of y value.
        :param rand_gen: Random numbers generator.
        :param randomize: Should the point be generated in random position?
        """
        if randomize:
            self.x_ = a + (b - a) * rand_gen.random()
            self.y_ = M * rand_gen.random()
        else:
            self.x_ = a
            self.y_ = b

    def is_under_graph(self, callback) -> bool:
        """
        Check if the point y value is lower than value of the function in given x

        :param callback: Function giving a float value.
        :return: Is the y value lower than value of the function in given x?
        """
        if self.y_ <= callback(self.x_):
            return True
        return False

    def distance_to_point(self, point) -> float:
        """
        Find the distance to given point in 2D space.

        :param point: Different point.
        :return: Distance.
        """
        assert isinstance(point, Point)
        return math.sqrt((point.x_ - self.x_) ** 2 + (point.y_ - self.y_) ** 2)

    def is_in_distance(self, point, distance: float) -> bool:
        """
        Check if distance to given point is lower of equal to given distance.

        :param point: Different point.
        :param distance: Distance limit.
        """
        assert isinstance(point, Point)
        if self.distance_to_point(point) <= distance:
            return True
        return False

    def __str__(self) -> str:
        """
        Change the way interpreter is printing this object.
        Function used for debugging.

        :return: String with points x and y coordinates.
        """
        return f'x={self.x_}, y={self.y_}'


def f_a(x: float) -> float:
    """
    Returns the value of the root of the third degree of x.

    :param x: X argument in range [0, 8]
    :return: Value of the function.
    """
    assert (x <= 8)
    assert (x >= 0)
    return x ** (1 / 3)


def f_b(x: float) -> float:
    """
    Returns the value of the sine of x.

    :param x: X argument in range [0, Pi]
    :return float: Value of the function.
    """
    assert x >= 0
    assert x <= math.pi
    return math.sin(x)


def f_c(x: float) -> float:
    """
    Returns the value of 4x(1-x)^3.

    :param x: X argument in range [0, 1] 
    :return: Value of the function.
    """
    assert x >= 0
    assert x <= 1
    return 4 * x * ((1 - x) ** 3)


def integral_approx(n: int, C: int, a: float, b: float, M: float) -> float:
    """
    Find an approximation of integral of given function.

    :param n: Number of generated points.
    :param C: Number of points "under graph of the function"
    :param a: Left limit of domain.
    :param b: Right limit of domain.
    :param M: Upper bound of the function values.
    :return: Approximation of the value of the integral.
    """
    return C / n * (b - a) * M


def find_fun_integral(rand_gen: random.SystemRandom,
                      a: float,
                      b: float,
                      M: float,
                      integ_value: float,
                      function) -> None:
    """
    Generate approximations of the integral of a function.
    This method finds approximations for given n = {50, 100, ... , 5000} points.
    Generate a diagram of the simulation after all calculations.

    :param rand_gen: Random numbers generator.
    :param a: Left limit of domain.
    :param b: Right limit of domain
    :param M: Upper bound of the function.
    :param integ_value: Value of the integral of the function.
    :param function: Function callback.
    """
    approx_results = {}
    for n in range(50, 5050, 50):
        approx_results[n] = []
        for k in range(0, 50):
            C = 0
            for i in range(0, n):
                point = Point(a, b, M, rand_gen)
                if point.is_under_graph(function):
                    C += 1
            approx_results[n].append(integral_approx(n, C, a, b, M))

    # arrange the results so that they can be shown on a plot
    x = np.arange(50, 5050, 50)
    values = [value for value in approx_results.values()]
    y = [value for value in values]
    for xe, ye in zip(x, y):
        plot.scatter([xe] * len(ye), ye, s=1.5, color='blue')

    # find mean approximation for each n
    mean_approx = [sum(values) / len(values) for values in approx_results.values()]
    plot.scatter(x, mean_approx, s=4, color='red')

    # add real value of integral to plot
    plot.axhline(y=integ_value, color='green')
    plot.show()


def find_pi_approx(rand_gen: random.SystemRandom,
                   a: float,
                   b: float,
                   M: float,
                   center_point: Point,
                   radius: float):
    """
    Find Pi value approximation.
    This method finds approximations for given n = {50, 100, ... , 5000} points.
    Generate a diagram of the simulation after all calculations.

    :param rand_gen: Random numbers generator.
    :param a: Left limit of domain.
    :param b: Right limit of domain.
    :param M: Upper bound of y of generated points.
    :param center_point: Center of the circle.
    :param radius: Radius of the circle.
    """
    approx_results = {}
    for n in range(50, 5050, 50):
        approx_results[n] = []
        for k in range(0, 50):
            C = 0
            for i in range(0, n):
                point = Point(a, b, M, rand_gen)
                if point.is_in_distance(center_point, radius):
                    C += 1
            approx_results[n].append(integral_approx(n, C, a, b, M))

    # arrange the results so that they can be shown on a plot
    x = np.arange(50, 5050, 50)
    values = [value for value in approx_results.values()]
    y = [value for value in values]
    for xe, ye in zip(x, y):
        plot.scatter([xe] * len(ye), ye, s=1.5, color='blue')

    # find mean approximation for each n
    mean_approx = [sum(values) / len(values) for values in approx_results.values()]
    plot.scatter(x, mean_approx, s=4, color='red')

    # add real value of integral to plot
    plot.axhline(y=math.pi, color='green')
    plot.show()


def main():
    # a function values
    f_a_a = 0.0
    f_a_b = 8.0
    M_a = f_a(f_a_b)
    a_integ_value = 12.0

    # b function values
    f_b_a = 0.0
    f_b_b = math.pi
    M_b = f_b(math.pi / 2.0)
    b_integ_value = 2.0

    # c function values
    f_c_a = 0.0
    f_c_b = 1.0
    M_c = f_c(0.25)
    c_integ_value = 0.2

    # set up the plot before showing data
    matplotlib.rcParams["figure.dpi"] = 100
    plot.axvline(x=0, color="black")
    rand_gen = random.SystemRandom()

    # leave one function uncommented to get corresponding graph with results
    find_fun_integral(rand_gen, f_a_a, f_a_b, M_a, a_integ_value, f_a)
    find_fun_integral(rand_gen, f_b_a, f_b_b, M_b, b_integ_value, f_b)
    find_fun_integral(rand_gen, f_c_a, f_c_b, M_c, c_integ_value, f_c)

    # pi approx function
    f_pi_a = 0.0
    f_pi_b = 2.0
    M_pi = 2.0
    center_point = Point(1.0, 1.0, randomize=False)
    radius = 1.0
    find_pi_approx(rand_gen, f_pi_a, f_pi_b, M_pi, center_point, radius)


if __name__ == '__main__':
    main()
