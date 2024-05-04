#include "gf.cpp"

class GF1234567891 : public GF1234577 {
    public:
        GF1234567891() {};
        GF1234567891(size_t val);
        GF1234567891(long long val);
        GF1234567891(int val);
        GF1234567891(const GF1234567891& other);
        GF1234567891(GF1234567891&& other);

        // arithmetic
        GF1234567891 operator+(const GF1234567891& other);
        GF1234567891 operator-(const GF1234567891& other);
        GF1234567891 operator*(const GF1234567891& other);
        GF1234567891 operator/(const GF1234567891& other);

        // assignments
        GF1234567891& operator=(const GF1234567891& other);
        GF1234567891& operator+=(const GF1234567891& other);
        GF1234567891& operator-=(const GF1234567891& other);
        GF1234567891& operator*=(const GF1234567891& other);
        GF1234567891& operator/=(const GF1234567891& other);

        static size_t Characteristic();
        size_t GetBody() override;
    private:
        static constexpr size_t BODY = 1234567891;  
};

GF1234567891::GF1234567891(size_t val) {
    value_ = val % GetBody();
}

GF1234567891::GF1234567891(long long val) {
    if(val < 0) {
        val *= -1;
        val %= GetBody();
        val = GetBody() - val;
    }
    value_ = val % GetBody();
}

GF1234567891::GF1234567891(int val) {
    if(val < 0) {
        val *= -1;
        val %= GetBody();
        val = GetBody() - val;
    }
    value_ = val % GetBody();
}

GF1234567891::GF1234567891(const GF1234567891& other) {
    value_ = other.value_;
}

GF1234567891::GF1234567891(GF1234567891&& other) {
    value_ = std::move(other.value_);
}

inline GF1234567891 GF1234567891::operator+(const GF1234567891& other) {
    return {(value_ + other.value_) % GetBody()};
}

inline GF1234567891 GF1234567891::operator-(const GF1234567891& other) {
    long long int val = value_ - other.value_;
    if(val < 0) {
        val = GetBody() + val;
    }
    return {(size_t)(val) % GetBody()};
}

inline GF1234567891 GF1234567891::operator*(const GF1234567891& other) {
    return {(value_ * other.value_) % GetBody()};
}

inline GF1234567891 GF1234567891::operator/(const GF1234567891& other) {
    size_t inverse = 1;
    while((inverse * other.value_) % GetBody() != 1 && inverse < GetBody()) {
        inverse++;
    }
    if(inverse == GetBody()) {
        throw std::runtime_error(std::to_string(other.value_) + " is not reversible.");
    }
    return {(value_ * inverse) % GetBody()};
}

inline GF1234567891& GF1234567891::operator=(const GF1234567891& other) {
    value_ = other.value_;
    return *this;
}

inline GF1234567891& GF1234567891::operator+=(const GF1234567891& other) {
    value_ = (value_ + other.value_) % GetBody();
    return *this;
}

inline GF1234567891& GF1234567891::operator-=(const GF1234567891& other) {
    long long val = value_ - other.value_;
    if(val < 0) {
        val = GetBody() - val;
    }
    value_ = (size_t)(val) % GetBody();
    return *this;
}

inline GF1234567891& GF1234567891::operator*=(const GF1234567891& other) {
    value_ = (value_ * other.value_) % GetBody();
    return *this;
}

inline GF1234567891& GF1234567891::operator/=(const GF1234567891& other) {
    size_t inverse = 1;
    while((inverse * other.value_) % GetBody() != 1 && inverse < GetBody()) {
        inverse++;
    }
    if(inverse == GetBody()) {
        throw std::runtime_error(std::to_string(other.value_) + " is not reversible.");
    }
    value_ = (value_ * inverse) % GetBody();
    return *this;
}

size_t GF1234567891::Characteristic() {
    return BODY;
}

size_t GF1234567891::GetBody() {
    return BODY;
}
