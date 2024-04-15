#include "gf.cpp"

int main() {
    GF1234577 a;
    GF1234577 b = -12345678;
    std::cin >> a;
    a += b;
    std::cout << a << " " << b << std::endl;
    std::cout << GF1234577::Characteristic() << std::endl;
}