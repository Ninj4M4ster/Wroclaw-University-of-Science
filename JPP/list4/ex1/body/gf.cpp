#include "gf.hpp"

GF1234577::GF1234577(size_t val) {
    value_ = val % GetBody();
}

GF1234577::GF1234577(long long val) {
    if(val < 0) {
        val *= -1;
        val %= GetBody();
        val = GetBody() - val;
    }
    value_ = val % GetBody();
}

GF1234577::GF1234577(int val) {
    if(val < 0) {
        val *= -1;
        val %= GetBody();
        val = GetBody() - val;
    }
    value_ = val % GetBody();
}

GF1234577::GF1234577(const GF1234577& other) {
    value_ = other.value_;
}

GF1234577::GF1234577(GF1234577&& other) {
    value_ = std::move(other.value_);
}

size_t GF1234577::Characteristic() {
    return BODY;
}

size_t GF1234577::GetBody() {
    return BODY;
}
