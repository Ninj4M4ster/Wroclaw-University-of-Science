class Gf1234577:
    BODY = 1234577

    # constructors 

    def __init__(self, val: int):
        if val < 0:
            val = -val
            val = val % self.BODY
            val = self.BODY - val

        self._value = val % self.BODY

    def __str__(self):
        return str(self._value)

    @staticmethod
    def Characteristic():
        counter = 1
        val = 1
        while val != 0:
            val += 1
            val %= Gf1234577.BODY
            counter += 1
        return counter

    # comparisons

    def __eq__(self, other):
        return self._value == other._value
    
    def __neq__(self, other):
        return self._value != other._value
    
    def __le__(self, other):
        return self._value <= other._value
    
    def __ge__(self, other):
        return self._value >= other._value

    def __lt__(self, other):
        return self._value < other._value
    
    def __gt__(self, other):
        return self._value > other._value
    
    # arithmetic

    def __add__(self, other):
        return (self._value + other._value) % self.BODY
    
    def __sub__(self, other):
        val = self._value - other._value
        if val < 0:
            val += self.BODY
        return val
    
    def __mul__(self, other):
        return (self._value * other._value) % self.BODY
    
    def __truediv__(self, other):
        inverse = 1
        while (inverse * other._value) % self.BODY != 1 and inverse < self.BODY:
            inverse += 1
        if inverse == self.BODY: 
            raise Exception(other._value, " is not reversible.")
        
        return (self._value * inverse) % self.BODY
    
    # assignments

    def __iadd__(self, other):
        self._value += other._value
        self._value %= self.BODY

    def __isub__(self, other):
        self._value -= other._value
        if self._value < 0:
            self._value += self.BODY

    def __imul__(self, other):
        self._value *= other._value
        self._value %= self.BODY

    def __idiv__(self, other):
        inverse = 1
        while (inverse * other._value) % self.BODY != 1 and inverse < self.BODY:
            inverse += 1
        if inverse == self.BODY: 
            raise Exception(other._value, " is not reversible.")
        
        self._value *= inverse
        self._value %= self.BODY