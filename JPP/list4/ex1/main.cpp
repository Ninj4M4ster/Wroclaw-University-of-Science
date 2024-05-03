#include "body/gf_child.hpp"
#include <memory>

int main() {
    std::shared_ptr<GF1234567891> body = std::make_shared<GF1234567891>(2);
    std::cout << *body.get() << std::endl;
}