#include "user/user.hpp"
#include <memory>

int main() {
    std::shared_ptr<DHSetup<GF1234567891>> dh_setup = std::make_shared<DHSetup<GF1234567891>>();

    GF1234567891 a = dh_setup->getGenerator();
    std::cout << a << std::endl;
}