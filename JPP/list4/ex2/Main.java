package main;

public class Main {
    public static void main(String[] args) throws Exception {
        DHSetup<GF1234567891> dh_setup = new DHSetup<>(new GF1234567891());

        GF1234567891 generator = dh_setup.getGenerator();
        System.out.println("Generator: " + generator.stringify());

        User<GF1234567891> user1 = new User<>(dh_setup);
        User<GF1234567891> user2 = new User<>(dh_setup);
        GF1234567891 pub_key_1 = user1.getPublicKey();
        GF1234567891 pub_key_2 = user2.getPublicKey();

        System.out.println("Public key user1: " + pub_key_1.stringify());
        System.out.println("Public key user2: " + pub_key_2.stringify());

        user1.setKey(pub_key_2);
        user2.setKey(pub_key_1);

        System.out.println("Encryption test 1 -> 2");
        GF1234567891 data = new GF1234567891(80L);
        System.out.println("Data: " + data.stringify());
        GF1234567891 encrypted_by_1 = user1.encrypt(data);
        System.out.println("Encrypted by user1: " + encrypted_by_1.stringify());
        GF1234567891 decrypted_by_2 = user2.decrypt(encrypted_by_1);
        System.out.println("Decrypted by user2: " + decrypted_by_2.stringify());

        System.out.println("Encryption test 2 -> 1");
        data.assign(50L);
        System.out.println("Data: " + data.stringify());
        GF1234567891 encrypted_by_2 = user2.encrypt(data);
        System.out.println("Encrypted by user2: " + encrypted_by_2.stringify());
        GF1234567891 decrypted_by_1 = user1.decrypt(encrypted_by_2);
        System.out.println("Decrypted by user1: " + decrypted_by_1.stringify());
    }
}
