#include "gf.cpp"

int main() {
    GF1234577 a;
    GF1234577 b = 5;
    std::cin >> a;
    a += b;
    std::cout << a << std::endl;
    std::cout << GF1234577::Characteristic() << std::endl;
}