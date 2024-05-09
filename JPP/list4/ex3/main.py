from body.gf_child import Gf1234567891
from dh_setup.dh_setup import DHSetup
from user.user import User

def main():
    dh_setup = DHSetup[Gf1234567891](Gf1234567891)

    generator = dh_setup.getGenerator()
    print(f'Generator: {generator}')
    user1 = User[Gf1234567891](dh_setup, Gf1234567891)
    user2 = User[Gf1234567891](dh_setup, Gf1234567891)
    pub_key_1 = user1.getPublicKey()
    pub_key_2 = user2.getPublicKey()

    print(f'Public key user1: {pub_key_1}')
    print(f'Public key user2: {pub_key_2}')

    user1.setKey(pub_key_2)
    user2.setKey(pub_key_1)

    print(f'Encryption test 1 -> 2')
    data = Gf1234567891(1000)
    print(f'Data: {data}')
    encrypted_by_1 = user1.encrypt(data)
    print(f'Encrypted by user1: {encrypted_by_1}')
    decrypted_by_2 = user2.decrypt(encrypted_by_1)
    print(f'Decrypted by user2: {decrypted_by_2}')

    print(f'Encryption test 2 -> 1')
    data = Gf1234567891(10)
    print(f'Data: {data}')
    encrypted_by_2 = user2.encrypt(data)
    print(f'Encrypted by user2: {encrypted_by_2}')
    decrypted_by_1 = user1.decrypt(encrypted_by_2)
    print(f'Decrypted by user1: {decrypted_by_1}')

main()