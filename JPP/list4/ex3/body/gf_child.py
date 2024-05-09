import body.gf

class Gf1234567891(body.gf.Gf1234577):
    BODY = 1234567891

    # constructors 

    def __init__(self, val: int):
        if val < 0:
            val = -val
            val = val % self.BODY
            val = self.BODY - val

        self._value = val % self.BODY

    @staticmethod
    def Characteristic():
        return 1234567891
    
    def construct(self, val: int):
        return Gf1234567891(val)
