
class NoNextValueException(Exception):
    """This is custom exception defined for the next_tuple function."""
    pass


def next_tuple(L, n, k):
    """This function finds next tuple in lexicographical order.

    It looks from the right for first number that is not the highest possible
    on given position.

    If there is no next tuple, it raises NoNextValueException.

    :param L: tuple
        It represents tuple for which function finds next value.
    :param n: int
        It represents the number of elements in a set of n consecutive natural values.
    :param k:
        It represents the number of elements in the subsets.
    :return: tuple
        Next tuple in order.
    """
    elements_count = k
    i = 0
    while k > 0:
        if L[k-1] == n - i:
            k -= 1
            i += 1
            continue
        else:
            new_item = list(L)
            new_item[k-1] += 1
            for index in range(k, elements_count):
                new_item[index] = new_item[index - 1] + 1
            return tuple(new_item)
    raise NoNextValueException("There is no higher value in your set.")


def gen_tuples(n, k):
    """This function generates all possible subsets of the set
    of form {1, 2, ... , n} in lexicographical order.

    :param n: int
        It represents the number of elements in a set of n consecutive natural values.
    :param k:
        It represents the number of elements in the subsets.
    """
    assert n > 0 and 0 < k <= n
    element = []
    # creating first and the smallest element for given parameters
    for i in range(1, k + 1):
        element.append(i)
    element = tuple(element)
    print(element)
    while True:
        try:
            element = next_tuple(element, n, k)
            print(element)
        except NoNextValueException:
            break


if __name__ == '__main__':
    gen_tuples(5, 3)
