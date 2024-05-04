#include "../dh_setup/dh_setup.hpp"
#include <memory>

template<typename T>
class User {
    public:
        User(std::shared_ptr<DHSetup<T>> dh_setup);

        T getPublicKey();
        void setKey(T a);
        T encrypt(T m);
        T decrypt(T c);

    private:
        std::shared_ptr<DHSetup<T>> dh_setup_;
        T encrypting_key_;
        bool key_set_ = false;
        size_t secret_;
};

template<typename T> 
User<T>::User(std::shared_ptr<DHSetup<T>> dh_setup) {
    dh_setup_ = dh_setup;
    size_t characteristic = T::Characteristic();
    std::uniform_int_distribution<size_t> dist(1, characteristic - 1);
    std::mt19937_64 rand_gen{std::random_device{}()};
    secret_ = dist(rand_gen);
}

template<typename T>
T User<T>::getPublicKey() {
    return dh_setup_->power(dh_setup_->getGenerator(), secret_);
}

template<typename T>
void User<T>::setKey(T a) {
    encrypting_key_ = dh_setup_->power(a, secret_);
    key_set_ = true;
}

template<typename T>
T User<T>::encrypt(T m) {
    if(!key_set_) {
        throw std::runtime_error();
    }
    return m * encrypting_key_;
}

template<typename T>
T User<T>::decrypt(T c) {
    if(!key_set_) {
        throw std::runtime_error();
    }
    return c / encrypting_key_;
}