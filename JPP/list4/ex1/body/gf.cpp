#include "gf.hpp"

GF1234577::GF1234577(size_t val) {
    value_ = val % BODY;
}

GF1234577::GF1234577(long long val) {
    if(val < 0) {
        val *= -1;
        val %= BODY;
        val = BODY - val;
    }
    value_ = val % BODY;
}

GF1234577::GF1234577(int val) {
    if(val < 0) {
        val *= -1;
        val %= BODY;
        val = BODY - val;
    }
    value_ = val % BODY;
}

GF1234577::GF1234577(const GF1234577& other) {
    value_ = other.value_;
}

GF1234577::GF1234577(GF1234577&& other) {
    value_ = std::move(other.value_);
}

size_t GF1234577::Characteristic() {
    size_t counter = 1;
    size_t val = 1;
    while(val != 0) {
        val++;
        val %= BODY;
        counter++;
    }
    return counter;
}
