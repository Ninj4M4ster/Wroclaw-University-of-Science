from typing import Type, TypeVar, Generic, List
import random
from body.gf import Gf1234577
import copy

T = TypeVar('T', bound=Gf1234577)

class DHSetup(Generic[T]):
    _body_generator: T = None
    _t_class: T = None
    def __init__(self, t_obj: Type[T]) -> None:
        self._t_class = t_obj
        characteristic = self._t_class.Characteristic() - 1
        print(f's {characteristic}')
        dividers = []
        for i in range(1, characteristic ** (1//2) + 1):
            if self.isNumberPrimary(i) and characteristic % i == 0:
                dividers.append(i)
        self._body_generator = self._t_class(random.randint(1, characteristic))
        while not self.isGeneratorLegal(dividers):
            self._body_generator = self._t_class(random.randint(1, characteristic))

    def isNumberPrimary(self, number) -> bool:
        if number <= 2:
            return True
        for i in range(2, number):
            if number % i == 0:
                return False
        return True
    
    def isGeneratorLegal(self, dividers):
        characteristic = self._t_class.Characteristic() - 1
        for val in dividers:
            if self._body_generator * self._t_class(characteristic / val) == self._t_class(1):
                return False
        return True
    
    def getGenerator(self) -> T:
        return self._body_generator
    
    def power(self, a: T, b: int):
        result = self._t_class(1)
        a_copy = copy.deepcopy(a)
        while b > 0:
            if b % 2 == 0:
                b /= 2
                a_copy *= a_copy
            else:
                b-=1
                result *= a_copy

                b /= 2
                a_copy *= a_copy
        return result