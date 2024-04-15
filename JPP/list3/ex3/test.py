from gf import Gf1234577 as GF

def main():
    a = GF(1234576)
    b = GF(2)
    a /= b
    print(a)
    print(GF.Characteristic())

main()