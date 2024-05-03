#ifndef GF_HPP
#define GF_HPP

#include <iostream>

class GF1234577 {
public:
    // constructors
    GF1234577() {};
    GF1234577(size_t val);
    GF1234577(long long val);
    GF1234577(int val);
    GF1234577(const GF1234577& other);
    GF1234577(GF1234577&& other);

    // conversions
    operator size_t() const;
    operator int() const;
    operator long long() const;
    operator unsigned int() const;

    // comparisons
    bool operator==(const GF1234577& other);
    bool operator!=(const GF1234577& other);
    bool operator<=(const GF1234577& other);
    bool operator>=(const GF1234577& other);
    bool operator<(const GF1234577& other);
    bool operator>(const GF1234577& other);

    // arithmetic
    GF1234577 operator+(const GF1234577& other);
    GF1234577 operator-(const GF1234577& other);
    GF1234577 operator*(const GF1234577& other);
    GF1234577 operator/(const GF1234577& other);

    // assignments
    GF1234577& operator=(const GF1234577& other);
    GF1234577& operator+=(const GF1234577& other);
    GF1234577& operator-=(const GF1234577& other);
    GF1234577& operator*=(const GF1234577& other);
    GF1234577& operator/=(const GF1234577& other);

    // streams
    friend std::ostream& operator<<(std::ostream& os, const GF1234577& obj);
    friend std::istream& operator>>(std::istream& os, GF1234577& obj);

    // characteristic
    static size_t Characteristic();

private:
    size_t value_;

protected:
    static constexpr size_t BODY = 1234577; 
};


inline GF1234577::operator size_t() const {
    return value_;
}

inline GF1234577::operator int() const {
    return static_cast<int>(value_);
}

inline GF1234577::operator long long() const {
    return static_cast<long long>(value_);
}

inline GF1234577::operator unsigned int() const {
    return static_cast<unsigned int>(value_);
}

inline bool GF1234577::operator==(const GF1234577& other) {
    return value_ == other.value_;
}

inline bool GF1234577::operator!=(const GF1234577& other) {
    return value_ != other.value_;
}

inline bool GF1234577::operator<=(const GF1234577& other) {
    return value_ <= other.value_;
}

inline bool GF1234577::operator>=(const GF1234577& other) {
    return value_ >= other.value_;
}

inline bool GF1234577::operator>(const GF1234577& other) {
    return value_ > other.value_;
}

inline bool GF1234577::operator<(const GF1234577& other) {
    return value_ < other.value_;
}

inline GF1234577 GF1234577::operator+(const GF1234577& other) {
    return {(value_ + other.value_) % BODY};
}

inline GF1234577 GF1234577::operator-(const GF1234577& other) {
    long long int val = value_ - other.value_;
    if(val < 0) {
        val = BODY + val;
    }
    return {(size_t)(val) % BODY};
}

inline GF1234577 GF1234577::operator*(const GF1234577& other) {
    return {(value_ * other.value_) % BODY};
}

inline GF1234577 GF1234577::operator/(const GF1234577& other) {
    size_t inverse = 1;
    while((inverse * other.value_) % BODY != 1 && inverse < BODY) {
        inverse++;
    }
    if(inverse == BODY) {
        throw std::runtime_error(std::to_string(other.value_) + " is not reversible.");
    }
    return {(value_ * inverse) % BODY};
}

inline GF1234577& GF1234577::operator=(const GF1234577& other) {
    value_ = other.value_;
    return *this;
}

inline GF1234577& GF1234577::operator+=(const GF1234577& other) {
    value_ = (value_ + other.value_) % BODY;
    return *this;
}

inline GF1234577& GF1234577::operator-=(const GF1234577& other) {
    long long val = value_ - other.value_;
    if(val < 0) {
        val = BODY - val;
    }
    value_ = (size_t)(val) % BODY;
    return *this;
}

inline GF1234577& GF1234577::operator*=(const GF1234577& other) {
    value_ = (value_ * other.value_) % BODY;
    return *this;
}

inline GF1234577& GF1234577::operator/=(const GF1234577& other) {
    size_t inverse = 1;
    while((inverse * other.value_) % BODY != 1 && inverse < BODY) {
        inverse++;
    }
    if(inverse == BODY) {
        throw std::runtime_error(std::to_string(other.value_) + " is not reversible.");
    }
    value_ = (value_ * inverse) % BODY;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const GF1234577& obj) {
    os << obj.value_;
    return os;
}

std::istream& operator>>(std::istream& os, GF1234577& obj) {
    os >> obj.value_;
    return os;
}

#endif  // GF_HPP