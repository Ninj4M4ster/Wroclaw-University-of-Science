#include "gf.cpp"

class GF1234567891 : public GF1234577 {
    public:
        GF1234567891() : GF1234577() {};
        GF1234567891(size_t val) : GF1234577(val) {};
        GF1234567891(long long val): GF1234577(val) {};
        GF1234567891(int val): GF1234577(val) {};
        GF1234567891(const GF1234577& other): GF1234577(other) {};
        GF1234567891(GF1234577&& other): GF1234577(other) {};
    private:
        static constexpr size_t BODY = 1234567891; 
};
