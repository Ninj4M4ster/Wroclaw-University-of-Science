#include "dh_setup.hpp"
#include "../body/gf_child.hpp"

template<typename T>
DHSetup<T>::DHSetup() {
    std::uniform_int_distribution<> distribution(1, T::Characteristic() - 1);
}