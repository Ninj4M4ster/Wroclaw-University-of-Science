from gf import Gf1234577 as GF

def main():
    a = GF(5)
    b = GF(27)
    print(f'a = {a}')
    print(f'b = {b}')
    print(f'{a} + {b} = {a + b}')
    print(f'{a} - {b} = {a - b}')
    print(f'{a} * {b} = {a * b}')
    print(f'{a} / {b} = {a / b}\n')
    
    print(f'{a} == {b} = {a == b}')
    print(f'{a} != {b} = {a != b}')
    print(f'{a} < {b} = {a < b}')
    print(f'{a} > {b} = {a > b}')
    print(f'{a} <= {b} = {a <= b}')
    print(f'{a} >= {b} = {a >= b}\n')

    print(f'Characteristic: {GF.Characteristic()}')

main()