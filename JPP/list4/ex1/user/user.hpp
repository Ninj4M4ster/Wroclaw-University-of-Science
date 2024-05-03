#include "../dh_setup/dh_setup.hpp"
#include <memory>

template<typename T>
class User {
    public:
        User(std::shared_ptr<DHSetup> dh_setup);

        T getPublicKey();
        void setKey(T a);
        T encrypt(T m);
        T decrypt(T c);

    private:
        T encrypting_key_;
};
