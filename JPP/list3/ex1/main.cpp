#include "gf.cpp"

int main() {
    GF1234577 a = 5;
    GF1234577 b = 27;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl << std::endl;
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << a << " - " << b << " = " << a - b << std::endl;
    std::cout << a << " * " << b << " = " << a * b << std::endl;
    std::cout << a << " / " << b << " = " << a / b << std::endl << std::endl;

    std::cout << a << " == " << b << " = " << (a == b) << std::endl;
    std::cout << a << " != " << b << " = " << (a != b) << std::endl;
    std::cout << a << " < " << b << " = " << (a < b) << std::endl;
    std::cout << a << " > " << b << " = " << (a > b) << std::endl;
    std::cout << a << " <= " << b << " = " << (a <= b) << std::endl;
    std::cout << a << " >= " << b << " = " << (a >= b) << std::endl << std::endl;

    size_t sum = a + b;
    long long diff = a - b;
    int a_p = a;
    unsigned int b_p = b;

    GF1234577 c(a);

    std::cout << "c = a; c = " << c << std::endl << std::endl;

    std::cout << "Characteristic: " << GF1234577::Characteristic() << std::endl;
}