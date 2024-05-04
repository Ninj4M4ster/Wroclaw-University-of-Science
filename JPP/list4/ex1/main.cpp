#include "user/user.hpp"
#include <memory>

int main() {
    using GF = GF1234567891;
    using DH = DHSetup<GF>;
    using UserGF = User<GF>;
    std::shared_ptr<DH> dh_setup = std::make_shared<DH>();

    GF generator = dh_setup->getGenerator();
    std::cout << "Generator: " << generator << std::endl;
    std::shared_ptr<UserGF> user1 = std::make_shared<UserGF>(dh_setup);
    std::shared_ptr<UserGF> user2 = std::make_shared<UserGF>(dh_setup);
    auto pub_key_1 = user1->getPublicKey();
    auto pub_key_2 = user2->getPublicKey();

    std::cout << "Public key user1: " << pub_key_1 << std::endl;
    std::cout << "Public key user2: " << pub_key_2 << std::endl;

    user1->setKey(pub_key_2);
    user2->setKey(pub_key_1);

    std::cout << "Encryption test 1 -> 2" << std::endl;
    size_t data = 20;
    std::cout << "Data: " << data << std::endl;
    auto encrypted_by_1 = user1->encrypt(data);
    std::cout << "Encrypted by user1: " << encrypted_by_1 << std::endl;
    auto decrypted_by_2 = user2->decrypt(encrypted_by_1);
    std::cout << "Decrypted by user2: " << decrypted_by_2 << std::endl;

    std::cout << "Encryption test 2 -> 1" << std::endl;
    data = 10;
    std::cout << "Data: " << data << std::endl;
    auto encrypted_by_2 = user2->encrypt(data);
    std::cout << "Encrypted by user2: " << encrypted_by_2 << std::endl;
    auto decrypted_by_1 = user1->decrypt(encrypted_by_2);
    std::cout << "Decrypted by user1: " << decrypted_by_1 << std::endl;
}