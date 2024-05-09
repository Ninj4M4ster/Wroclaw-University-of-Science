import math

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
    
    def construct(self, val: int):
        return Gf1234577(val)

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
        return self.construct((self._value + other._value) % self.BODY)
    
    def __sub__(self, other):
        val = self._value - other._value
        if val < 0:
            val += self.BODY
        return self.construct(val)
    
    def __mul__(self, other):
        return self.construct((self._value * other._value) % self.BODY)
    
    def __truediv__(self, other):
        res_x, res_y, err = self.dioph(self.BODY, other._value, 1)
        while res_y < 0:
            res_y += self.BODY
        if err != 0: 
            raise Exception(other._value, " is not reversible.")
        
        return self.construct((self._value * res_y) % self.BODY)
    
    # assignments

    def __iadd__(self, other):
        self._value += other._value
        self._value %= self.BODY
        return self

    def __isub__(self, other):
        self._value -= other._value
        if self._value < 0:
            self._value += self.BODY
        return self

    def __imul__(self, other):
        self._value *= other._value
        self._value %= self.BODY
        return self

    def __idiv__(self, other):
        res_x, res_y, err = self.dioph(self.BODY, other._value, 1)
        while(res_y < 0):
            res_y += self.BODY
        if err != 0: 
            raise Exception(other._value, " is not reversible.")
        
        self._value *= res_y
        self._value %= self.BODY
        return self
    
    def gcm(self, a, b):
        while(b != 0):
            a, b = b, a % b
        return a
    
    def dioph(self, a, b, c):
        result_x = 0
        result_y = 0
        result_error_status = 0
        reversed = False
        a_p = -a if a < 0 else a
        b_p = -b if b < 0 else b
        d = self.gcm(a_p, b_p)
        if d == 0:  # a and b == 0:
            if c != 0:
                result_error_status = 1
        elif c % d != 0: # no result available
            result_error_status = 2
        else:
            if a < b:
                p = a
                a = b
                b = p
                reversed = 1
            x = 1
            y = 0
            if b != 0:
                div_result = 0
                div_rest = 1
                x_temp = 0
                y_temp = 1
                while div_rest != 0:  # extended euklides algorithm
                    div_result = a // b
                    div_rest = a % b
                    a = b
                    b = div_rest
                    
                    helper_x_temp = x_temp
                    helper_y_temp = y_temp
                    x_temp = x - div_result * x_temp
                    y_temp = y - div_result * y_temp
                    x = helper_x_temp
                    y = helper_y_temp
            if reversed:
                result_x = y
                result_y = x
            else:
                result_x = x
                result_y = y
            s = c // d
            result_x *= s
            result_y *= s
        return result_x, result_y, result_error_status